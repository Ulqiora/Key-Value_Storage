#include "BTree.h"

namespace s21 {

BTree::BTree(int newlevel) : IDataOperations() {
  if (newlevel > MAX_ORDER_OF_NODE || newlevel < MIN_ORDER_OF_NODE)
    throw std::invalid_argument("Incorrect value in constructor!");
  degree_ = newlevel;
}
BTree::~BTree() {
  thread_to_del_->CheckEnd();
  th_.join();
  delete root_;
}

bool BTree::RootIsFull() {
  return root_->keyValues.size() == (long unsigned int)(2 * degree_ - 1);
}

bool BTree::Set(const Key &key, const Value &value) {
  if (root_ == nullptr) {
    root_ = new NodeBTree(degree_, true);
    root_->keyValues.push_back(new std::pair<Key, Value>(key, value));
    root_->descendants.push_back(nullptr);
    root_->descendants.push_back(nullptr);
    return true;
  }
  if (Exists(key)) return false;
  if (RootIsFull()) {
    NodeBTree *newRoot = new NodeBTree(degree_, false);
    newRoot->descendants.push_back(root_);
    newRoot->SplitDescendants(0, root_);
    int i = 0;
    if (newRoot->keyValues[0]->first < key) i++;
    newRoot->descendants[i]->Insert(key, value);
    root_ = newRoot;
  } else {
    root_->Insert(key, value);
  }
  return true;
}

void BTree::NodeBTree::Insert(const Key &key, const Value &value) {
  int indexRightestElem = keyValues.size() - 1;
  if (NodeIsLeaf()) {
    while (indexRightestElem >= 0 && keyValues[indexRightestElem]->first > key)
      indexRightestElem--;
    keyValues.insert(keyValues.begin() + indexRightestElem + 1,
                     new std::pair<Key, Value>(key, value));
    descendants.insert(descendants.begin() + indexRightestElem + 1, nullptr);
  } else {
    while (indexRightestElem >= 0 && keyValues[indexRightestElem]->first > key)
      indexRightestElem--;
    if (descendants[indexRightestElem + 1]->IsFull()) {
      SplitDescendants(indexRightestElem + 1,
                       descendants[indexRightestElem + 1]);
      if (keyValues[indexRightestElem + 1]->first < key) indexRightestElem++;
    }
    descendants[indexRightestElem + 1]->Insert(key, value);
  }
}

void BTree::NodeBTree::SplitDescendants(int indexDescendants,
                                        NodeBTree *splitedNode) {
  NodeBTree *z = new NodeBTree(splitedNode->degree_, splitedNode->is_leaf_);
  z->keyValues.resize(degree_ - 1);
  std::copy(splitedNode->keyValues.begin() + degree_,
            splitedNode->keyValues.end(), z->keyValues.begin());
  splitedNode->keyValues.erase(splitedNode->keyValues.begin() + degree_,
                               splitedNode->keyValues.end());
  if (!splitedNode->NodeIsLeaf()) {
    z->descendants.resize(degree_);
    std::copy(splitedNode->descendants.begin() + degree_,
              splitedNode->descendants.end(), z->descendants.begin());
    splitedNode->descendants.erase(splitedNode->descendants.begin() + degree_,
                                   splitedNode->descendants.end());
  } else {
    splitedNode->descendants.resize(degree_);
    z->descendants.resize(degree_);
  }
  descendants.insert(descendants.begin() + indexDescendants + 1, z);
  auto last = splitedNode->keyValues[degree_ - 1];
  auto index = std::find_if(keyValues.begin(), keyValues.end(),
                            [last](std::pair<Key, Value> *temp) {
                              return temp->first >= last->first;
                            });
  keyValues.insert(index, last);
  splitedNode->keyValues.pop_back();
}

std::optional<BTree::Value> BTree::Get(const Key &key) {
  std::lock_guard lg(mtx_);
  if (!root_) return std::nullopt;
  auto findedPair = root_->FindValueByKey(key);
  if (findedPair) return findedPair->second;
  return std::nullopt;
}

std::pair<BTree::Key, BTree::Value> *BTree::NodeBTree::FindValueByKey(
    const Key &key) {
  for (int i = 0; (long unsigned int)i < keyValues.size(); ++i) {
    if (keyValues[i]->first == key) {
      return (keyValues[i]);
    } else if (keyValues[i]->first > key && descendants[i] != nullptr) {
      return descendants[i]->FindValueByKey(key);
    } else if (((long unsigned int)i == (keyValues.size() - 1)) &&
               (keyValues[i]->first < key) && (descendants[i + 1] != nullptr)) {
      return descendants[i + 1]->FindValueByKey(key);
    }
  }
  return nullptr;
}

bool BTree::Exists(const Key &key) {
  std::lock_guard lg(mtx_);
  if (!root_) return false;
  return !(root_->FindValueByKey(key) == nullptr);
}

bool BTree::Update(const Key &key, const Value &value) {
  std::lock_guard lg(mtx_);
  if (!root_) return false;
  std::pair<Key, Value> *findedPair = root_->FindValueByKey(key);
  if (findedPair != nullptr) findedPair->second = value;
  return findedPair != nullptr;
}

std::vector<BTree::Key> BTree::Keys() {
  std::lock_guard lg(mtx_);
  if (!root_) return std::vector<BTree::Key>();
  return root_->GetKeys();
}
std::vector<BTree::Key> BTree::NodeBTree::GetKeys() {
  std::vector<Key> result;
  if (is_leaf_) {
    result.reserve(keyValues.size());
    for (size_t i = 0; i < keyValues.size(); i++) {
      result.push_back(keyValues[i]->first);
    }
  } else {
    result.reserve(keyValues.size());
    for (int i = 0; (long unsigned int)i < keyValues.size(); i++) {
      auto keysDescendents = descendants[i]->GetKeys();
      for (size_t j = 0; j < keysDescendents.size(); j++) {
        result.push_back(keysDescendents[j]);
      }
      result.push_back(keyValues[i]->first);
    }
    auto keysDescendents = descendants[descendants.size() - 1]->GetKeys();
    std::transform(keysDescendents.begin(), keysDescendents.end(),
                   keysDescendents.begin(),
                   [&result](IDataOperations::Key key) -> IDataOperations::Key {
                     result.push_back(key);
                     return key;
                   });
  }
  return result;
}

bool BTree::Rename(const Key &prev, const Key &updated) {
  std::lock_guard lg(mtx_);
  if (!root_) return false;
  auto ptr = root_->FindValueByKey(prev);
  if (!ptr) return false;
  if (!Del(prev)) return false;
  auto res = Set(updated, ptr->second);
  if (res) thread_to_del_->Rename(prev, updated);
  return res;
}

bool s21::BTree::Del(const Key &key) {
  std::lock_guard lg(mtx_);
  if (!root_) return false;
  if (!Exists(key)) return false;
  root_->Deletion(key);
  if (root_->descendants.size() == 1) {
    NodeBTree *temp = root_;
    if (root_->is_leaf_) {
      root_ = nullptr;
    } else {
      root_ = root_->descendants[0];
    }
    temp->descendants.resize(0);
    delete temp;
  }
  return true;
}

int BTree::NodeBTree::FindValueByKeyCurrNode(const Key &key) {
  return std::find_if(keyValues.begin(), keyValues.end(),
                      [&key](std::pair<Key, Value> *temp) {
                        return temp->first >= key;
                      }) -
         keyValues.begin();
}

void BTree::NodeBTree::Deletion(const Key &key) {
  auto index = FindValueByKeyCurrNode(key);
  if ((long unsigned int)index < keyValues.size() &&
      keyValues[index]->first == key) {
    if (is_leaf_) {
      RemoveFromLeaf(index);
    } else {
      RemoveFromNotLeaf(index);
    }
  } else {
    if (is_leaf_) return;
    if (descendants[index]->keyValues.size() < (long unsigned int)degree_) {
      Fill(index);
    }
    descendants[index]->Deletion(key);
  }
  return;
}

void BTree::NodeBTree::RemoveFromLeaf(int index) {
  delete keyValues[index];
  keyValues.erase(keyValues.begin() + index);
  descendants.erase(descendants.begin());
}

void BTree::NodeBTree::RemoveFromNotLeaf(int index) {
  if (descendants[index]->keyValues.size() >= (long unsigned int)degree_) {
    auto pred = GetPredecessor(index);
    std::swap(*pred, keyValues[index]);
    descendants[index]->Deletion((*pred)->first);
  } else if (descendants[index + 1]->keyValues.size() >=
             (long unsigned int)degree_) {
    auto succ = GetSuccessor(index);
    std::swap(*succ, keyValues[index]);
    descendants[index + 1]->Deletion((*succ)->first);
  } else {
    auto temp = keyValues[index]->first;
    Merge(index);
    descendants[index]->Deletion(temp);
  }
}

std::pair<s21::BTree::Key, s21::BTree::Value>
    **BTree::NodeBTree::GetPredecessor(int index) {
  NodeBTree *cur = descendants[index];
  while (!cur->is_leaf_) {
    cur = cur->descendants[cur->keyValues.size()];
  }
  return &(cur->keyValues[cur->keyValues.size() - 1]);
}

std::pair<s21::BTree::Key, s21::BTree::Value> **BTree::NodeBTree::GetSuccessor(
    int index) {
  NodeBTree *cur = descendants[index + 1];
  while (!cur->is_leaf_) {
    cur = cur->descendants[0];
  }
  return &(cur->keyValues[0]);
}

void BTree::NodeBTree::Fill(int index) {
  if (index != 0 &&
      descendants[index - 1]->keyValues.size() >= (long unsigned int)degree_) {
    BorrowFromPrev(index);
  } else if (((long unsigned int)index) != keyValues.size() &&
             descendants[index + 1]->keyValues.size() >=
                 (long unsigned int)degree_) {
    BorrowFromNext(index);
  } else {
    if ((long unsigned int)index != keyValues.size())
      Merge(index);
    else
      Merge(index - 1);
  }
}

void BTree::NodeBTree::BorrowFromPrev(int index) {
  NodeBTree *child = descendants[index];
  NodeBTree *sibling = descendants[index - 1];
  child->keyValues.push_front(keyValues[index - 1]);
  child->descendants.push_front(sibling->descendants.back());
  sibling->descendants.pop_back();
  keyValues[index - 1] = sibling->keyValues.back();
  sibling->keyValues.pop_back();
}

void BTree::NodeBTree::BorrowFromNext(int index) {
  NodeBTree *child = descendants[index];
  NodeBTree *sibling = descendants[index + 1];
  child->keyValues.push_back(keyValues[index]);
  child->descendants.push_back(sibling->descendants.front());
  sibling->descendants.pop_front();
  keyValues[index] = sibling->keyValues.front();
  sibling->keyValues.pop_front();
}

void BTree::NodeBTree::Merge(int index) {
  NodeBTree *child = descendants[index];
  NodeBTree *sibling = descendants[index + 1];
  child->keyValues.push_back(keyValues[index]);
  for (auto &kv : sibling->keyValues) {
    child->keyValues.push_back(kv);
    kv = nullptr;
  }
  for (auto &descendant : sibling->descendants) {
    child->descendants.push_back(descendant);
    descendant = nullptr;
  }
  keyValues.erase(keyValues.begin() + index);
  descendants.erase(descendants.begin() + index + 1);
  sibling->keyValues.resize(0);
  sibling->descendants.resize(0);
  delete sibling;
}

std::optional<std::vector<BTree::Key>> BTree::Find(const Value &value) {
  std::lock_guard lg(mtx_);
  auto temp = root_->FindKeysByValue(value);
  std::sort(temp.begin(), temp.end());
  return temp;
}
std::vector<BTree::Key> BTree::NodeBTree::FindKeysByValue(const Value &value) {
  std::vector<Key> result;
  for (auto kv : keyValues) {
    if (kv->second == value) result.push_back(kv->first);
  }
  if (!is_leaf_) {
    for (auto desc : descendants) {
      auto temp = desc->FindKeysByValue(value);
      std::copy(temp.begin(), temp.end(), std::back_inserter(result));
    }
  }
  return result;
}

std::vector<DataS21Student> BTree::ShowAll() {
  std::lock_guard lg(mtx_);
  if (!root_) return std::vector<DataS21Student>();
  return root_->getAllValues();
}

std::vector<DataS21Student> BTree::NodeBTree::getAllValues() {
  std::vector<DataS21Student> result;
  for (auto i = 0; (long unsigned int)i < keyValues.size(); i++) {
    if (!is_leaf_) {
      auto temp = std::move(descendants[i]->getAllValues());
      result.insert(result.end(), temp.begin(), temp.end());
    }
    result.push_back(keyValues[i]->second);
  }
  if (!is_leaf_) {
    auto temp = std::move(descendants.back()->getAllValues());
    result.insert(result.end(), temp.begin(), temp.end());
  }
  return result;
}

int BTree::Export(const std::filesystem::path &filename) {
  std::lock_guard lg(mtx_);
  std::ofstream file(filename);
  if (file.is_open()) {
    int res{0};
    if (root_) {
      res += root_->PrintInfo(file);
    }
    file.close();
    return res;
  }
  return 0;
}
int BTree::NodeBTree::PrintInfo(std::ofstream &file) {
  int result = 0;
  for (auto i = 0; (long unsigned int)i < keyValues.size(); i++) {
    if (!is_leaf_) result += descendants[i]->PrintInfo(file);
    file << std::left << std::setw(10) << keyValues[i]->first
         << keyValues[i]->second << '\n';
    result++;
  }
  if (!is_leaf_) result += descendants.back()->PrintInfo(file);
  return result;
}

int BTree::Upload(const std::filesystem::path &filename) {
  std::lock_guard lg(mtx_);
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::invalid_argument("This file " + filename.string() +
                                " is not opened!");
  }
  Value tempValue;
  Key tempKey;
  std::string currline;
  int i = 0;
  while (std::getline(file, currline)) {
    std::stringstream currLineStream{currline};
    currLineStream >> tempKey;
    currLineStream >> tempValue;
    Set(tempKey, tempValue);
    i++;
  }
  file.close();
  return i;
}

}  // namespace s21

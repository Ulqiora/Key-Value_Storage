#include "SelfBalancingBinarySearchTree.h"

bool s21::SelfBalancingBinarySearchTree::Set(const Key &key,
                                             const Value &value) {
  std::lock_guard lg(mtx_);
  return tree_.insert(key, value).second;
}

std::optional<s21::SelfBalancingBinarySearchTree::Value>
s21::SelfBalancingBinarySearchTree::Get(const Key &key) {
  std::lock_guard lg(mtx_);
  if (!Exists(key)) return std::nullopt;
  return tree_[key];
}

bool s21::SelfBalancingBinarySearchTree::Exists(const Key &key) {
  std::lock_guard lg(mtx_);
  return tree_.contains(key) ? true : false;
}

bool s21::SelfBalancingBinarySearchTree::Del(const Key &key) {
  std::lock_guard lg(mtx_);
  if (!tree_.contains(key)) return false;
  auto it = tree_.find(key);
  tree_.erase(it);
  return true;
}

bool s21::SelfBalancingBinarySearchTree::Update(const Key &key,
                                                const Value &value) {
  std::lock_guard lg(mtx_);
  if (!tree_.contains(key)) return false;
  auto iter = tree_.find(key);
  if (value.GetFirstname() != "-")
    (*iter).second.SetFirstname(value.GetFirstname());
  if (value.GetLastname() != "-")
    (*iter).second.SetLastname(value.GetLastname());
  if (value.GetCity() != "-") (*iter).second.SetCity(value.GetCity());
  if (value.GetYear() != -1) (*iter).second.SetYear(value.GetYear());
  if (value.GetCoins() != -1) (*iter).second.SetCoins(value.GetCoins());

  return true;
}

std::vector<s21::SelfBalancingBinarySearchTree::Key>
s21::SelfBalancingBinarySearchTree::Keys() {
  std::lock_guard lg(mtx_);
  std::vector<Key> res;
  if (!tree_.empty()) {
    for (auto it = tree_.begin(); it != tree_.end(); ++it) {
      auto pair = *it;
      res.push_back(pair.first);
    }
  }
  return res;
}

bool s21::SelfBalancingBinarySearchTree::Rename(const Key &key,
                                                const Key &new_key) {
  std::lock_guard lg(mtx_);
  if (!tree_.contains(key) || tree_.contains(new_key)) return false;

  auto iter = tree_.find(key);
  tree_.insert(new_key, (*iter).second);
  thread_to_del_->Rename(key, new_key);
  tree_.erase(iter);
  return true;
}

std::optional<std::vector<s21::SelfBalancingBinarySearchTree::Key>>
s21::SelfBalancingBinarySearchTree::Find(const Value &value) {
  std::lock_guard lg(mtx_);
  std::vector<Key> res;
  if (!tree_.empty()) {
    for (auto it = tree_.begin(); it != tree_.end(); ++it) {
      if (((*it).second.GetFirstname() == value.GetFirstname() ||
           value.GetFirstname() == "-") &&
          ((*it).second.GetLastname() == value.GetLastname() ||
           value.GetLastname() == "-") &&
          ((*it).second.GetYear() == value.GetYear() ||
           value.GetYear() == -1) &&
          ((*it).second.GetCity() == value.GetCity() ||
           value.GetCity() == "-") &&
          ((*it).second.GetCoins() == value.GetCoins() ||
           value.GetCoins() == -1))
        res.push_back((*it).first);
    }
  }

  return res.size() != 0 ? std::optional<std::vector<Key>>{res} : std::nullopt;
}

std::vector<s21::SelfBalancingBinarySearchTree::Value>
s21::SelfBalancingBinarySearchTree::ShowAll() {
  std::lock_guard lg(mtx_);
  std::vector<Value> res;
  if (!tree_.empty()) {
    for (auto it = tree_.begin(); it != tree_.end(); ++it) {
      auto pair = *it;
      res.push_back(pair.second);
    }
  }
  return res;
}

int s21::SelfBalancingBinarySearchTree::Upload(
    const std::filesystem::path &filename) {
  std::lock_guard lg(mtx_);
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::invalid_argument("No such file!");
  }
  std::string line;
  int counter = 0;

  while (getline(file, line)) {
    CleanLine(line);

    if (CheckStruct(line)) {
      std::string key;
      s21::DataS21Student value;
      std::stringstream ss(line);
      ss >> key >> value;

      if (Set(key, value)) counter++;
    }
  }
  file.close();
  return counter;
}

void s21::SelfBalancingBinarySearchTree::CleanLine(std::string &line) {
  for (std::string::size_type i = 0; i < line.size(); ++i) {
    if (line[i] == ' ') continue;
    if (!std::isalnum(static_cast<unsigned char>(line[i]))) {
      line.erase(i, 1);
      i--;
    }
  }
}

int s21::SelfBalancingBinarySearchTree::Export(
    const std::filesystem::path &filename) {
  std::lock_guard lg(mtx_);
  std::ofstream file;
  file.open(filename);

  int counter = 0;
  if (!tree_.empty()) {
    for (auto it = tree_.begin(); it != tree_.end(); ++it) {
      file << (*it).first;
      file << (*it).second.ToStdString() << std::endl;
      counter++;
    }
  }

  file.close();
  return counter;
}

#pragma once

#include <algorithm>
#include <deque>
#include <exception>
#include <numeric>

#include "../IDataOperations.h"

namespace s21 {
class BTree : public IDataOperations {
  using Key = std::string;
  using Value = DataS21Student;

 private:
  struct NodeBTree {
   public:
    bool is_leaf_;
    int degree_;
    std::deque<std::pair<Key, Value>*> keyValues;
    std::deque<NodeBTree*> descendants;

   public:
    NodeBTree() = delete;
    NodeBTree(int newDegree, bool leaf) : is_leaf_(leaf), degree_(newDegree) {}
    ~NodeBTree() {
      if (!is_leaf_) {
        for (auto descendant : descendants) {
          delete descendant;
        }
      }
      for (auto keyValue : keyValues) {
        delete keyValue;
      }
    }

    bool IsFull() {
      return keyValues.size() == (long unsigned int)(degree_ * 2 - 1);
    }
    void Insert(const Key&, const Value&);
    void SplitDescendants(int indexDescendants, NodeBTree* splitedNode);
    bool NodeIsLeaf() { return is_leaf_ == true; }
    std::pair<Key, Value>* FindValueByKey(const Key&);
    std::vector<Key> GetKeys();
    void Deletion(const Key& key);
    int FindValueByKeyCurrNode(const Key& key);
    void RemoveFromLeaf(int index);
    void RemoveFromNotLeaf(int index);
    std::pair<Key, Value>** GetPredecessor(int idx);
    std::pair<Key, Value>** GetSuccessor(int idx);
    void Fill(int idx);
    void BorrowFromPrev(int idx);
    void BorrowFromNext(int idx);
    void Merge(int idx);
    std::vector<Key> FindKeysByValue(const Value& value);
    std::vector<DataS21Student> getAllValues();
    int PrintInfo(std::ofstream& file);
  };

 public:
  explicit BTree(int newlevel = 2);
  BTree(const BTree& other) = delete;
  BTree(const BTree&& other) = delete;
  BTree& operator=(const BTree& other) = delete;
  BTree& operator=(const BTree&& other) = delete;
  ~BTree() final;

  bool Set(const Key& key, const Value& value) final;
  std::optional<Value> Get(const Key&) final;
  bool Exists(const Key&) final;
  bool Del(const Key&) final;
  bool Update(const Key&, const Value&) final;
  std::vector<Key> Keys() final;
  bool Rename(const Key& prev, const Key& updated) final;
  std::optional<std::vector<Key>> Find(const Value& value) final;
  std::vector<DataS21Student> ShowAll() final;
  int Upload(const std::filesystem::path& filename) final;
  int Export(const std::filesystem::path&) final;

  // void PrintToGraphViz(const std::string&);

 private:
  int degree_;
  NodeBTree* root_ = nullptr;

  const static int MAX_ORDER_OF_NODE = 10000;
  const static int MIN_ORDER_OF_NODE = 2;

 private:
  bool RootIsFull();
};
}  // namespace s21

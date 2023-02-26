#pragma once

#include "../IDataOperations.h"
#include "s21_map.h"

namespace s21 {
class SelfBalancingBinarySearchTree : public IDataOperations {
  using Key = std::string;
  using Value = DataS21Student;

 public:
  SelfBalancingBinarySearchTree() : IDataOperations() {}
  SelfBalancingBinarySearchTree(const SelfBalancingBinarySearchTree& other) =
      delete;
  SelfBalancingBinarySearchTree(const SelfBalancingBinarySearchTree&& other) =
      delete;
  SelfBalancingBinarySearchTree& operator=(
      const SelfBalancingBinarySearchTree& other) = delete;
  SelfBalancingBinarySearchTree& operator=(
      const SelfBalancingBinarySearchTree&& other) = delete;
  ~SelfBalancingBinarySearchTree() {
    thread_to_del_->CheckEnd();
    th_.join();
  };

  bool Set(const Key& key, const Value& value) final;
  std::optional<s21::DataS21Student> Get(const Key& key) final;
  bool Exists(const Key& key) final;
  bool Del(const Key& key) final;
  bool Update(const Key& key, const Value& value) final;
  std::vector<Key> Keys() final;
  bool Rename(const Key& key, const Key& new_key) final;
  std::optional<std::vector<Key>> Find(const Value& value) final;
  std::vector<Value> ShowAll() final;
  int Upload(const std::filesystem::path& filename) final;
  int Export(const std::filesystem::path& filename) final;

 private:
  s21::map<Key, Value> tree_;

  void CleanLine(std::string& line);
};
}  // namespace s21

#pragma once

#include "Model/BTree/BTree.h"
#include "Model/HashTable/HashTable.h"
#include "Model/SelfBalancingBinarySearchTree/SelfBalancingBinarySearchTree.h"

namespace s21 {
class Controller {
 public:
  void SetHashTable() {
    if (!model_) {
      delete model_;
    }
    model_ = new s21::HashTable();
  }
  void SelfBalancingBinarySearchTree() {
    if (!model_) {
      delete model_;
    }
    model_ = new s21::SelfBalancingBinarySearchTree();
  }
  void SetBTree() {
    if (!model_) {
      delete model_;
    }
    model_ = new s21::BTree(2);
  }
  bool Set(const std::string& key, const DataS21Student& value) {
    return model_->Set(key, value);
  }
  bool Set(const std::string& key, const DataS21Student& value,
           const std::chrono::seconds& time) {
    return model_->Set(key, value, time);
  }
  std::optional<s21::DataS21Student> Get(const std::string& key) {
    return model_->Get(key);
  }
  bool Exists(const std::string& key) { return model_->Exists(key); }
  bool Del(const std::string& key) { return model_->Del(key); }
  bool Update(const std::string& key, const DataS21Student& value) {
    return model_->Update(key, value);
  }
  std::vector<std::string> Keys() { return model_->Keys(); }
  bool Rename(const std::string& key, const std::string& new_key) {
    return model_->Rename(key, new_key);
  }
  int TTL(const std::string& key) { return model_->TTL(key); }
  std::optional<std::vector<std::string>> Find(const DataS21Student& value) {
    return model_->Find(value);
  }
  std::vector<DataS21Student> Showall() { return model_->ShowAll(); }
  int Upload(const std::filesystem::path& filename) {
    return model_->Upload(filename);
  }
  int Export(const std::filesystem::path& filename) {
    return model_->Export(filename);
  }

 private:
  IDataOperations* model_ = nullptr;
};
}  // namespace s21

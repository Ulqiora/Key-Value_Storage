#ifndef SRC_HASH_TABLE_H_
#define SRC_HASH_TABLE_H_

#include <bitset>
#include <iostream>
#include <string>

#include "../DataS21Student.h"
#include "../IDataOperations.h"

namespace s21 {
class HashTable : public IDataOperations {
 public:
  using Key = std::string;
  using Value = DataS21Student;
  HashTable() : IDataOperations() { hash_data_.resize(actual_size_); }
  HashTable(const HashTable&) = delete;
  HashTable(const HashTable&&) = delete;
  HashTable& operator=(const HashTable&) = delete;
  HashTable& operator=(const HashTable&&) = delete;

  virtual ~HashTable() {
    for (auto i = hash_data_.begin(); i < hash_data_.end(); ++i) {
      s21::HashTable::HashTableTrio* tmp = *i;
      while (tmp) {
        s21::HashTable::HashTableTrio* last = tmp;
        tmp = tmp->next;
        delete last;
      }
    }
    thread_to_del_->CheckEnd();
    th_.join();
  }

  bool Del(const Key&) override;
  bool Exists(const Key&) override;
  std::vector<Key> Keys() override;
  std::vector<Value> ShowAll() override;
  bool Set(const Key&, const Value&) override;
  bool Rename(const Key&, const Key&) override;
  bool Update(const Key&, const Value&) override;
  int Upload(const std::filesystem::path&) override;
  int Export(const std::filesystem::path&) override;
  std::optional<s21::DataS21Student> Get(const Key&) override;
  std::optional<std::vector<Key>> Find(const Value&) override;

 private:
  struct HashTableTrio {
    Key key;
    Value value;
    HashTableTrio* next;
  };

  std::vector<int>::size_type actual_size_ = 17;
  std::vector<HashTableTrio*> hash_data_;

  size_t GenerateKey(Key);
  s21::DataS21Student* GetFValue(const Key&);
  void CleanLine(std::string&);
};

}  // namespace s21

#endif  // ! SRC_HASH_TABLE_H_

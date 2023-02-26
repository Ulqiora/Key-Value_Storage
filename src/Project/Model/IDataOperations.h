#pragma once

#include <chrono>
#include <filesystem>
#include <optional>
#include <vector>

#include "DataS21Student.h"
#include "ThreadsDel/ThreadsDel.h"

namespace s21 {

class IDataOperations {
 public:
  using Key = std::string;
  using Value = DataS21Student;

  IDataOperations() : thread_to_del_(new ThreadsDel(mtx_)) {
    th_ = std::move(std::thread{&ThreadsDel::Start, thread_to_del_, this});
  }
  IDataOperations(const IDataOperations& other) = delete;
  IDataOperations(const IDataOperations&& other) = delete;
  IDataOperations& operator=(const IDataOperations& other) = delete;
  IDataOperations& operator=(const IDataOperations&& other) = delete;
  virtual ~IDataOperations() { delete thread_to_del_; }

  virtual bool Set(const Key&, const Value&) = 0;
  virtual bool Set(const Key& key, const Value& value,
                   const std::chrono::seconds& sec) {
    bool res = Set(key, value);
    if (res) thread_to_del_->AddPair(key, sec);
    return res;
  }
  virtual std::optional<s21::DataS21Student> Get(const Key& key) = 0;
  virtual bool Exists(const Key&) = 0;
  virtual bool Del(const Key&) = 0;
  virtual bool Update(const Key&, const Value&) = 0;
  virtual std::vector<Key> Keys() = 0;
  virtual bool Rename(const Key&, const Key&) = 0;
  int TTL(const Key& key) { return thread_to_del_->GetRest(key); };
  virtual std::optional<std::vector<Key>> Find(const Value&) = 0;
  virtual std::vector<Value> ShowAll() = 0;
  virtual int Upload(const std::filesystem::path&) = 0;
  virtual int Export(const std::filesystem::path&) = 0;

 protected:
  s21::ThreadsDel* thread_to_del_ = nullptr;
  std::recursive_mutex mtx_;
  std::thread th_;
};
}  // namespace s21

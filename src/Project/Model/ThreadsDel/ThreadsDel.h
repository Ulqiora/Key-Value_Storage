#pragma once

#include <algorithm>
#include <list>
#include <mutex>
#include <thread>

namespace s21 {
class IDataOperations;

class ThreadsDel {
 public:
  ThreadsDel() = delete;
  explicit ThreadsDel(std::recursive_mutex& mtx_);
  ThreadsDel(const ThreadsDel& other) = delete;
  ThreadsDel(const ThreadsDel&& other) = delete;
  ThreadsDel& operator=(const ThreadsDel& other) = delete;
  ThreadsDel& operator=(const ThreadsDel&& other) = delete;
  ~ThreadsDel() {}

  void CheckEnd();
  int GetRest(const std::string& key);
  void Start(IDataOperations* transaction);
  void Rename(const std::string& prev, const std::string& updated);
  void AddPair(const std::string& key, const std::chrono::seconds& sec);

 private:
  using threadsdel_pair =
      std::pair<std::chrono::system_clock::time_point, std::string>;
  std::list<threadsdel_pair> pairs_;
  std::recursive_mutex& mtx_;
  bool is_end_ = false;
};
}  // namespace s21

#include "ThreadsDel.h"

#include "../IDataOperations.h"

s21::ThreadsDel::ThreadsDel(std::recursive_mutex &mtx) : pairs_(0), mtx_(mtx) {}

void s21::ThreadsDel::Start(IDataOperations *transaction) {
  while (!is_end_) {
    while (!pairs_.empty()) {
      auto i = pairs_.begin();
      if (i->first < std::chrono::system_clock::now()) {
        transaction->Del(i->second);
        std::lock_guard lg(mtx_);
        pairs_.erase(i);
      }
    }
  }
}

void s21::ThreadsDel::AddPair(const std::string &key,
                              const std::chrono::seconds &sec) {
  auto time_for_del = std::chrono::system_clock::now() + sec;
  std::lock_guard lc(mtx_);
  auto index = pairs_.begin();
  for (; index != pairs_.end() && index->first < time_for_del; index++) {
  }
  pairs_.insert(index, {time_for_del, key});
}

void s21::ThreadsDel::CheckEnd() { is_end_ = true; }

void s21::ThreadsDel::Rename(const std::string &prev,
                             const std::string &updated) {
  std::lock_guard lc(mtx_);
  auto founded = std::find_if(
      pairs_.begin(), pairs_.end(),
      [&prev](const threadsdel_pair &pair) { return pair.second == prev; });
  if (founded != pairs_.end()) {
    founded->second = updated;
  }
}

int s21::ThreadsDel::GetRest(const std::string &key) {
  std::lock_guard lc(mtx_);
  auto iter = std::find_if(
      pairs_.begin(), pairs_.end(),
      [&key](const threadsdel_pair &temp) { return temp.second == key; });
  if (iter == pairs_.end()) return -1;
  if (iter->first < std::chrono::system_clock::now()) return -1;
  return (std::chrono::duration_cast<std::chrono::seconds>(
              iter->first - std::chrono::system_clock::now()))
      .count();
}

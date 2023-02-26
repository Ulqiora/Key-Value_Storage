#include "HashTable.h"
namespace s21 {

size_t HashTable::GenerateKey(Key key_v) {
  size_t size = 0, mul = 1, str_size = key_v.size();
  std::string binary_string = "";
  for (long unsigned int i = 0; i < str_size; ++i) {
    binary_string += std::bitset<8>(key_v[i]).to_string();
  }
  str_size = binary_string.size();
  for (long unsigned int j = 0; j < str_size; ++j, ++mul) {
    size += binary_string[j] * mul;
  }
  return size % actual_size_;
}

bool HashTable::Set(const Key &key, const Value &value) {
  std::lock_guard lg(mtx_);
  if (Exists(key)) return 0;
  size_t hash = GenerateKey(key);
  HashTableTrio *find = hash_data_[hash];
  HashTableTrio *temp_hash = new HashTableTrio();
  temp_hash->key = key;
  temp_hash->value = value;
  temp_hash->next = nullptr;
  if (hash_data_.size() < hash) hash_data_.resize(hash * 3);
  if (!find) {
    hash_data_[hash] = temp_hash;
    return true;
  } else if ((!find->next)) {
    hash_data_[hash]->next = temp_hash;
    return true;
  }
  while (find->next) find = find->next;
  find->next = temp_hash;

  return 0;
}

bool HashTable::Exists(const Key &key) {
  std::lock_guard lg(mtx_);
  return Get(key) != std::nullopt;
}

bool HashTable::Del(const Key &key) {
  std::lock_guard lg(mtx_);
  if (!Exists(key)) return 0;
  int hash = GenerateKey(key);
  HashTableTrio *buf = hash_data_[hash];
  HashTableTrio *prev = nullptr;
  HashTableTrio *tmp = nullptr;
  while (buf->key != key) {
    prev = buf;
    buf = buf->next;
  }
  if (!(buf->next)) {
    delete buf;
    if (prev) {
      prev->next = nullptr;
    } else {
      hash_data_[hash] = nullptr;
    }
  } else {
    buf->value = buf->next->value;
    buf->key = buf->next->key;
    tmp = buf->next;
    buf->next = buf->next->next;
    delete tmp;
  }
  return 1;
}

bool HashTable::Update(const Key &key, const Value &value) {
  std::lock_guard lg(mtx_);
  if (!Exists(key)) return 0;
  auto data = GetFValue(key);
  *data = value;
  return 1;
}

std::vector<HashTable::Key> HashTable::Keys() {
  std::lock_guard lg(mtx_);
  return Find({"-", "-", -1, "-", -1}).has_value()
             ? Find({"-", "-", -1, "-", -1}).value()
             : std::vector<HashTable::Key>{};
}

bool HashTable::Rename(const Key &old_key, const Key &new_key) {
  std::lock_guard lg(mtx_);
  if (!Exists(old_key)) return 0;
  HashTableTrio *old = hash_data_[GenerateKey(old_key)];
  while (old->key != old_key) {
    old = old->next;
  }
  auto old_value = Get(old_key);
  Del(old->key);
  if (Set(new_key, old_value.value())) {
    thread_to_del_->Rename(old_key, new_key);
  } else {
    return 0;
  }

  return 1;
}

std::optional<std::vector<HashTable::Key>> HashTable::Find(const Value &value) {
  std::lock_guard lg(mtx_);
  std::vector<Key> result;
  size_t size = hash_data_.size();
  for (long unsigned int i = 0; i < size; ++i) {
    HashTableTrio *find = hash_data_[i];
    while (find) {
      if (find->value == value) {
        result.push_back(find->key);
      }
      find = find->next;
    }
  }
  std::optional<std::vector<Key>> res{result};
  return result.size() ? res : std::nullopt;
}

std::vector<HashTable::Value> HashTable::ShowAll() {
  std::vector<Value> result;
  size_t size = hash_data_.size();
  for (long unsigned int i = 0; i < size; ++i) {
    HashTableTrio *find = hash_data_[i];
    while (find) {
      result.push_back(find->value);
      find = find->next;
    }
  }
  return result;
}

int HashTable::Upload(const std::filesystem::path &filename) {
  std::lock_guard lg(mtx_);
  int count = 0;
  Key key, str;
  Value value;
  std::ifstream file(filename);
  if (file.is_open()) {
    while (std::getline(file, str)) {
      CleanLine(str);
      if (CheckStruct(str)) {
        std::stringstream ss(str);
        ss >> key >> value;
        Set(key, value);
        ++count;
      }
    }
  }
  file.close();
  return count;
}

void HashTable::CleanLine(std::string &line) {
  for (std::string::size_type i = 0; i < line.size(); ++i) {
    if (line[i] == ' ') continue;
    if (!std::isalnum(static_cast<unsigned char>(line[i]))) {
      line.erase(i, 1);
      i--;
    }
  }
}

int HashTable::Export(const std::filesystem::path &filename) {
  std::lock_guard lg(mtx_);
  std::ofstream file;
  file.open(filename);
  std::vector<Key> key = Keys();
  int count = 0;
  if (file.is_open()) {
    for (auto i = key.begin(); i < key.end(); ++i) {
      file << *i << ' ' << Get(*i).value().ToStdString() << '\n';
      ++count;
    }
  }
  file.close();
  return count;
}

std::optional<s21::DataS21Student> HashTable::Get(const Key &key) {
  std::lock_guard lg(mtx_);
  s21::DataS21Student *result = GetFValue(key);
  if (!result) return std::nullopt;
  return *result;
}

s21::DataS21Student *HashTable::GetFValue(const Key &key) {
  HashTableTrio *find = hash_data_[GenerateKey(key)];
  while (find && find->key != key) {
    find = find->next;
  }
  if (find) {
    return &(find->value);
  }
  return nullptr;
}

}  // namespace s21

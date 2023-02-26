#ifndef SRC_S21_MAP_H_
#define SRC_S21_MAP_H_

#include "s21_set.h"

namespace s21 {

template <typename Key, typename T>
class map : public set<std::pair<Key, T>> {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<key_type, mapped_type>;
  using size_type = size_t;
  using iterator = typename set<value_type>::iterator;
  using reference = value_type&;
  using const_reference = const value_type&;
  using const_iterator = typename set<value_type>::const_iterator;
  using Node = typename set<value_type>::Node;

  class map_i : public set<Key>::iterator {};

  map() : set<std::pair<Key, T>>(), flag_insert_or_assign(false) {}
  ~map() { this->clear(); }
  explicit map(std::initializer_list<value_type> const& items);
  map(const map& copy);
  map(map&& copy);
  map& operator=(map&& m);

  std::pair<iterator, bool> insert(const Key& key, const T& obj);
  std::pair<iterator, bool> insert(const value_type& value);
  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);
  bool contains(const Key& key);
  T& at(const Key& key);
  T& operator[](const Key& key);
  iterator find(const Key& key);

 protected:
  Node* node_finder(Node* node, key_type value);
  bool flag_insert_or_assign;
};

template <typename Key, typename T>
typename std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const value_type& value) {
  return set<std::pair<Key, T>>::insert(value);
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::Node*
map<key_type, mapped_type>::node_finder(Node* node, key_type value) {
  Node* tmp = node;
  if (tmp) {
    if (value > tmp->x.first) {
      tmp = node_finder(tmp->right, value);
    } else if (value < tmp->x.first) {
      tmp = node_finder(tmp->left, value);
    } else if (value == tmp->x.first && flag_insert_or_assign) {
      return tmp;
    }
  }
  return tmp;
}

template <typename Key, typename T>
typename std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const Key& key, const T& obj) {
  std::pair<iterator, bool> rez;
  if (contains(key)) {   // CHANGED
    rez.second = false;  // CHANGED
    return rez;          // CHANGED
  } else {               // CHANGED
    value_type temp(key, obj);
    return rez = insert(temp);
  }
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::find(const Key& key) {
  iterator rez;
  rez.get_current() = node_finder(this->root_, key);
  return rez;
}

template <typename Key, typename T>
typename std::pair<typename map<Key, T>::iterator, bool>
map<Key, T>::insert_or_assign(const Key& key, const T& obj) {
  std::pair<iterator, bool> rez;
  flag_insert_or_assign = true;
  Node* tmp = node_finder(this->root_, key);
  if (tmp) {
    tmp->x.second = obj;
    rez.first.get_current() = tmp;
    rez.second = true;
  } else {
    rez = insert(key, obj);
  }
  flag_insert_or_assign = false;
  return rez;
}

template <typename key_type, typename mapped_type>
map<key_type, mapped_type>::map(std::initializer_list<value_type> const& items)
    : map() {
  for (auto& value : items) {
    insert(value);
  }
}

template <typename key_type, typename mapped_type>
map<key_type, mapped_type>::map(const map<key_type, mapped_type>& other)
    : map() {
  for (auto& value : other) insert(value);
}

template <typename key_type, typename mapped_type>
map<key_type, mapped_type>::map(map<key_type, mapped_type>&& other) : map() {
  this->clear();
  this->swap(other);
  other.root_ = nullptr;
}

template <typename key_type, typename mapped_type>
map<key_type, mapped_type>& map<key_type, mapped_type>::operator=(
    map<key_type, mapped_type>&& m) {
  map<key_type, mapped_type> buf(m);
  this->clear();
  this->swap(buf);
  return *this;
}

template <typename K, typename T>
T& map<K, T>::at(const K& key) {
  Node* rez = node_finder(this->root_, key);
  if (!rez) throw std::out_of_range("No elem");
  return rez->x.second;
}

template <typename K, typename T>
T& map<K, T>::operator[](const K& key) {
  Node* rez = node_finder(this->root_, key);
  return rez->x.second;
}

template <typename Key, typename T>
bool map<Key, T>::contains(const Key& key) {
  return node_finder(this->root_, key);
}

}  // namespace s21

#endif  // SRC_S21_MAP_H_

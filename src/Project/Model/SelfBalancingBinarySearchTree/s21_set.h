#ifndef SRC_S21_SET_H_
#define SRC_S21_SET_H_

#include <iostream>
#include <limits>
#include <stack>

namespace s21 {
template <typename K>
class set {
 protected:
  struct Node {
    K x;
    int height;
    Node *left;
    Node *right;
    explicit Node(K const &key)
        : x(key), height(1), left(nullptr), right(nullptr) {}
  };

  std::allocator<Node> n_;
  using Node_manage = std::allocator_traits<std::allocator<Node>>;
  using value_type = K;
  using key_type = value_type;
  using size_type = size_t;

  Node *root_;
  size_type size_ = 0;

  void del(Node *&node);
  Node *balance(Node *p);
  void fix_height(Node *p);
  int height(Node *p) { return p ? p->height : 0; }
  int bfactor(Node *p) { return height(p->right) - height(p->left); }
  Node *rotate_left(Node *q);
  Node *rotate_right(Node *p);
  Node *node_remover(Node *node, key_type value);
  Node *find_next_min(Node *node);
  Node *remove_min(Node *node);
  Node *node_finder(Node *node, key_type value, std::stack<Node *> &st_);
  Node *node_finder(Node *node, key_type value);

 public:
  set();
  explicit set(std::initializer_list<value_type> const &items);
  explicit set(const set &other);
  explicit set(set &&other);
  ~set();
  set &operator=(set &&other);

  class iterator {
   protected:
    friend set;
    std::stack<Node *> st_;
    Node *root_, *current_;
    Node *go_far_left(Node *t);
    int itercomplit_;

   public:
    Node *&get_current() { return this->current_; }
    std::stack<Node *> &get_st() { return this->st_; }

    explicit iterator(Node *tree = nullptr) : root_(tree) {
      itercomplit_ = 0;
      current_ = go_far_left(root_);
    }
    key_type &operator*() { return current_->x; }
    void operator++();
    bool operator!=(const iterator &other) {
      return itercomplit_ != other.itercomplit_;
    }
    bool operator==(const iterator &other) { return current_ = other.current_; }
  };
  class const_iterator : public iterator {
   public:
    explicit const_iterator(Node *tree = nullptr) : iterator(tree) {}

    void operator=(set<K>::iterator &&other) {
      this->root_ = other.root_;
      this->current_ = other.current_;
      this->st_ = other.st_;
    }

    const key_type &operator*() { return this->current_->x; }
  };
  friend class iterator;

  iterator begin() const;
  iterator end() const;

  const_iterator cbegin() const;
  const_iterator cend() const;

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  void clear();
  std::pair<iterator, bool> insert(const value_type &value);
  void erase(iterator pos);
  void swap(set &other);
  void merge(set &other);

  iterator find(const key_type &key);
  bool contains(const key_type &key);

  template <typename... Args>
  std::pair<iterator, bool> emplace(Args &&...args);

 private:
  Node *insert_rec(Node *p, const value_type &k, std::pair<iterator, bool> &it);
};

template <typename key_type>
set<key_type>::set() : root_(nullptr) {}

template <typename key_type>
set<key_type>::set(std::initializer_list<value_type> const &items)
    : root_(nullptr) {
  for (auto &value : items) {
    insert(value);
  }
}

template <typename key_type>
set<key_type>::set(const set<key_type> &other) : set() {
  for (auto &value : other) insert(value);
}

template <typename key_type>
set<key_type>::set(set<key_type> &&other) : root_(nullptr) {
  clear();
  swap(other);
  other.root_ = nullptr;
}

template <typename key_type>
set<key_type>::~set() {
  clear();
}

template <typename key_type>
set<key_type> &set<key_type>::operator=(set<key_type> &&other) {
  set<key_type> buf(other);
  clear();
  swap(buf);
  return *this;
}

template <typename key_type>
typename set<key_type>::iterator set<key_type>::begin() const {
  set::iterator rez(root_);
  return rez;
}

template <typename key_type>
typename set<key_type>::iterator set<key_type>::end() const {
  set::iterator rez;
  rez.itercomplit_ = 1;
  return rez;
}

template <typename key_type>
typename set<key_type>::const_iterator set<key_type>::cbegin() const {
  set::const_iterator rez(root_);
  return rez;
}

template <typename key_type>
typename set<key_type>::const_iterator set<key_type>::cend() const {
  set::const_iterator rez;
  rez.itercomplit_ = 1;
  return rez;
}

template <typename key_type>
void set<key_type>::iterator::operator++() {
  if (itercomplit_) {
    throw std::out_of_range("iterator traversed the entire list");
  }
  while (!st_.empty() && st_.top()->x < current_->x) {
    st_.pop();
  }
  if (current_->right != nullptr) {
    current_ = go_far_left(current_->right);
  } else if (!st_.empty()) {
    current_ = st_.top();
    st_.pop();
  } else {
    itercomplit_ = 1;
  }
}

template <typename key_type>
typename set<key_type>::Node *set<key_type>::iterator::go_far_left(Node *t) {
  if (t == nullptr) return nullptr;
  while (t->left != nullptr) {
    st_.push(t);
    t = t->left;
  }
  return t;
}

template <typename key_type>
bool set<key_type>::empty() const noexcept {
  return size() == 0;
}

template <typename key_type>
typename set<key_type>::size_type set<key_type>::size() const noexcept {
  return size_;
}

template <typename key_type>
typename set<key_type>::size_type set<key_type>::max_size() const noexcept {
  return Node_manage::max_size(n_);
}

template <typename key_type>
void set<key_type>::clear() {
  if (root_ != nullptr) {
    del(root_);
  }
  size_ = 0;
}

template <typename key_type>
void set<key_type>::del(Node *&node) {
  if (node != nullptr) {
    del(node->left);
    del(node->right);
    delete node;
    node = nullptr;
  }
}

template <typename key_type>
typename std::pair<typename set<key_type>::iterator, bool>
set<key_type>::insert(const value_type &value) {
  std::pair<iterator, bool> rez;
  rez.second = true;
  root_ = insert_rec(root_, value, rez);
  ++size_;
  return rez;
}

template <typename key_type>
typename set<key_type>::Node *set<key_type>::insert_rec(
    Node *p, const value_type &k, std::pair<iterator, bool> &it) {
  if (!p) return it.first.current_ = new Node(k);
  if (p->x == k) {
    it.first.current_ = p;
    it.second = false;
    return it.first.current_;
  }
  it.first.st_.push(p);
  if (k < p->x)
    p->left = insert_rec(p->left, k, it);
  else
    p->right = insert_rec(p->right, k, it);
  return balance(p);
}

template <typename key_type>
typename set<key_type>::Node *set<key_type>::balance(Node *p) {
  fix_height(p);
  if (bfactor(p) == 2) {
    if (p->right && bfactor(p->right) < 0) p->right = rotate_right(p->right);
    return rotate_left(p);
  }
  if (bfactor(p) == -2) {
    if (p->left && bfactor(p->left) > 0) p->left = rotate_left(p->left);
    return rotate_right(p);
  }
  return p;
}

template <typename key_type>
void set<key_type>::fix_height(Node *p) {
  int hl = height(p->left);
  int hr = height(p->right);
  p->height = (hl > hr ? hl : hr) + 1;
}

template <typename key_type>
typename set<key_type>::Node *set<key_type>::rotate_right(Node *p) {
  Node *q = p->left;
  p->left = q->right;
  q->right = p;
  fix_height(p);
  fix_height(q);
  return q;
}

template <typename key_type>
typename set<key_type>::Node *set<key_type>::rotate_left(Node *q) {
  Node *p = q->right;
  q->right = p->left;
  p->left = q;
  fix_height(q);
  fix_height(p);
  return p;
}

template <typename key_type>
void set<key_type>::erase(iterator pos) {
  root_ = node_remover(root_, pos.current_->x);
  --size_;
}

template <typename key_type>
typename set<key_type>::Node *set<key_type>::node_remover(Node *node,
                                                          key_type value) {
  if (!node) return 0;
  if (value < node->x) {
    node->left = node_remover(node->left, value);
  } else if (value > node->x) {
    node->right = node_remover(node->right, value);
  } else {
    Node *q = node->left;
    Node *r = node->right;
    delete (node);
    if (!r) return q;
    Node *min = find_next_min(r);
    min->right = remove_min(r);
    min->left = q;
    return balance(min);
  }
  return balance(node);
}

template <typename key_type>
typename set<key_type>::Node *set<key_type>::find_next_min(Node *node) {
  return node->left ? find_next_min(node->left) : node;
}

template <typename key_type>
typename set<key_type>::Node *set<key_type>::remove_min(Node *node) {
  if (node->left == 0) return node->right;
  node->left = remove_min(node->left);
  return balance(node);
}

template <typename key_type>
void set<key_type>::swap(set<key_type> &other) {
  Node *tmp = this->root_;
  this->root_ = other.root_;
  other.root_ = tmp;
  size_type ssize = size_;
  size_ = other.size_;
  other.size_ = ssize;
}

template <typename key_type>
void set<key_type>::merge(set<key_type> &other) {
  if (!other.empty()) {
    set<key_type> tmp(other);
    auto it = tmp.begin();
    while (it != tmp.end()) {
      if (contains(*it) == 0) {
        insert(*it);
        other.erase(it);
      }
      ++it;
    }
  }
}

template <typename key_type>
typename set<key_type>::iterator set<key_type>::find(const key_type &key) {
  iterator rez;
  rez.root_ = root_;
  rez.current_ = node_finder(root_, key, rez.st_);
  return rez;
}

template <typename key_type>
typename set<key_type>::Node *set<key_type>::node_finder(
    Node *node, key_type value, std::stack<Node *> &st_) {
  Node *tmp = node;
  if (!tmp->left && !tmp->right) {
    tmp = node;
  } else if (tmp) {
    st_.push(tmp);
    if (value > tmp->x) {
      tmp = node_finder(tmp->right, value, st_);
    } else if (value < tmp->x) {
      tmp = node_finder(tmp->left, value, st_);
    }
  }
  return tmp;
}

template <typename key_type>
typename set<key_type>::Node *set<key_type>::node_finder(Node *node,
                                                         key_type value) {
  Node *tmp = node;
  if (tmp) {
    if (value > tmp->x) {
      tmp = node_finder(tmp->right, value);
    } else if (value < tmp->x) {
      tmp = node_finder(tmp->left, value);
    }
  }
  return tmp;
}

template <typename key_type>
bool set<key_type>::contains(const key_type &key) {
  return node_finder(root_, key) ? true : false;
}

template <typename key_type>
template <typename... Args>
typename std::pair<typename set<key_type>::iterator, bool>
set<key_type>::emplace(Args &&...args) {
  return this->insert(key_type(args...));
}

}  // namespace s21

#endif  // SRC_S21_SET_H_

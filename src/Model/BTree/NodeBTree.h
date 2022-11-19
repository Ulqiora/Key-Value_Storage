#pragma once
#include <algorithm>
#include <array>
#include <memory>
#include <typeinfo>
#include <vector>

namespace s21 {
template <typename Key, typename Value>
class NodeBtree {
    //              CONSTRUCTORS AND DESTRUCTOR
 public:
    NodeBtree(size_t newLevel, bool typeNew) : NodeBtree(newLevel) { isLeaf = typeNew; }
    NodeBtree(size_t newLevel) : keyValues(0), descendents(0), level(newLevel) {
        descendents.reserve(2 * level);
        keyValues.reserve(2 * level - 1);
        bool = false;
    }
    NodeBtree() = delete;
    NodeBtree(const NodeBtree<Key, Value>&) = delete;
    NodeBtree(NodeBtree<Key, Value>&&) = default;

 public:
    void setType(bool type) { isLeaf = type; }
    int getLevel() { return level; }
    bool leaf() { return isLeaf; }
    size_t isCompleted() { return keyValues.size() == level - 1; }
    size_t getSizeKeyVal() { return keyValues.size(); }
    //                 INSERT
 public:
    void insertForNullRoot(const Key& key, const Value& value) {
        std::pair<Key, Value>* keyvalue = new std::pair<Key, Value>(key, value);
        keyValues.insert(keyvalue);
    }
    void splitDescendents(int index, NodeBtree<Key, Value>* node) {
        NodeBtree<Key, Value>* tempNode = new NodeBtree<Key, Value>(level, node->isLeaf);
    }
    void insert(const Key& key, const Value& value) {}
    std::pair<Key, Value>* getDescendent(int i) { return keyValues[i]; }

    //          Class Fields
 private:
    std::vector<std::pair<Key, Value>*> keyValues;
    std::vector<NodeBtree<Key, Value>*> descendents;

    size_t level;
    bool isLeaf;
};
}  // namespace s21
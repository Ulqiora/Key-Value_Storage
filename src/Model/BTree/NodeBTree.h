#pragma once
#include <algorithm>
#include <array>
#include <memory>
#include <vector>
#include <typeinfo>

namespace s21 {
enum class TypeOfNode {
    ROOT = 0,
    OTHER = 1,
    LEAF = 2,
};
template <typename Key, typename Value>
class NodeBtree {
   private:
    std::vector<std::shared_ptr<std::pair<Key, Value>>> keyValues;
    std::vector<std::shared_ptr<NodeBtree<Key, Value>>> descendents;
    std::weak_ptr<NodeBtree<Key, Value>> parent;
    size_t level;
    TypeOfNode type;

   private:

   public:
    NodeBtree(size_t newLevel, TypeOfNode typeNew) : NodeBtree(newLevel) { type = typeNew; }
    void setType(TypeOfNode);
    void setParent(NodeBtree<Key, Value>* parent);
    NodeBtree(size_t newLevel) : keyValues(0), descendents(0), level(newLevel) {
        descendents.reserve(level);
        keyValues.reserve(level - 1);
        type = TypeOfNode::ROOT;
    }
    NodeBtree() = delete;
    NodeBtree(const NodeBtree<Key, Value>&) = delete;
    NodeBtree(NodeBtree<Key, Value>&&) = default;
    int getLevel() { return level; }
    TypeOfNode getType() { return type; }
    size_t isCompleted() { return keyValues.size() == level - 1; }
    size_t getSizeKeyVal(){return keyValues.size();}
//                 INSERT
    public:
    void simpleInsert(const Key& key, const Value& value){
        auto iter = std::find_if(keyValues.begin(), keyValues.end(),
                                         [&key](auto i) { return i->first > key; });
        std::shared_ptr<std::pair<Key, Value>> keyvalue(new std::pair<Key, Value>(key, value));
        keyValues.insert(iter, keyvalue);
    }
};
}  // namespace s21
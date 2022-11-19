#pragma once
#include <algorithm>
#include <array>
#include <memory>
#include <vector>
#include <typeinfo>

namespace s21 {
enum class TypeOfNode {
    ROOT = 0,
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
    NodeBtree(size_t newLevel, TypeOfNode typeNew) : NodeBtree(newLevel) { type = typeNew; }
    void setType(TypeOfNode);
    void setParent(NodeBtree<Key, Value>* parent);

   public:
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




//                 INSERT
    public:
    void insert(const Key& key, const Value& value) {
        if (type == TypeOfNode::ROOT) {
            if (isCompleted()) {
                insertForComplitedNodeRoot(key, value);
            } else {
                auto iter = std::find_if(keyValues.begin(), keyValues.end(),
                                         [&key](auto i) { return i->first > key; });
                std::shared_ptr<std::pair<Key, Value>> keyvalue(new std::pair<Key, Value>(key, value));
                keyValues.insert(iter, keyvalue);
            }
        }
    }
    void simpleInsert(const Key& key, const Value& value){
        insert 
    }
   private:
    void insertForComplitedNodeRoot(const Key& key, const Value& value) {
        int meduim = keyValues.size() / 2.0;
        parent=std::make_shared<NodeBtree<Key,Value>>(NodeBtree<Key,Value>(level,type));
    }
    void divisionRoot(){
        
    }
};
}  // namespace s21
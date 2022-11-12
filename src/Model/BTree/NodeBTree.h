#pragma once
#include <memory>
#include <array>
#include <vector>
namespace s21{
enum class TypeOfNode{ ROOT=0, STANDART=1, LEAF=2,};
template <typename Key,typename Value, int level>
class NodeBtree{
    public:
    TypeOfNode type;
    std::vector<std::pair<Key,Value>> keyValue;
    std::vector<std::shared_ptr<NodeBtree>> descendents;
    NodeBtree() : keyValue(0), descendents(level, nullptr) {}
    NodeBtree(Key key,Value value){
        keyValue.push_back(std::pair<Key,Value>(key,value));
    }
    int getLevel(){
        return level;
    }
    
};
}
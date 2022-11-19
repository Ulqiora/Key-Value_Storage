#pragma onve
#include "../IDataOperations.h"
#include "NodeBTree.h"
namespace s21 {
template <typename Key, typename Value>
class Btree : public IDataOperations<Key, Value> {
   private:
    const static int MAX_ORDER_OF_NODE = 10000;
    int orderOfBTree = 0;
    int levelTree=0;
    NodeBtree<Key, Value> root;

   public:
    void SET(const Key& key,const Value& value) final {
        currNode=root;
        if(isEmpty()){
            levelTree++;
            root = new NodeBtree<Key,Value>(key,value);
        } else if(root->descendents.size()!=orderOfBTree){
            // auto found = std::find_if(currNode->keyValue.begin(), currNode->keyValue.end(),findFirstLarger);
            
        }
    }
    Value GET(const Key&) final {}
    bool EXISTS(const Key&) final {}
    bool DEL(const Key&) final {}
    void UPDATE(const Key&, const Value&) final {}
    std::vector<Key> KEYS() final {}
    void RENAME(const Key&, const Key&) final {}
    void TTL(const Key&) final {}
    std::vector<Key> FIND(const Value&) final {}
    void SHOWALL() final {}
    void UPLOAD(const std::string&) final {}
    void EXPORT(const std::string&) final {}

   public:
    Btree() = delete;
    Btree(int valueOfOrder) {
        if (valueOfOrder < 2) throw std::invalid_argument("Unacceptable value for the BTree order!");
        orderOfBTree = valueOfOrder;
    }
    Btree(const Btree&) = delete;
    Btree(Btree&&) = delete;
    virtual ~Btree() {}

   public:
    int getOrder() { return orderOfBTree; }
    private:
    bool isEmpty(){return root==nullptr || root->keyValue.size()==0;}
};
}  // namespace s21
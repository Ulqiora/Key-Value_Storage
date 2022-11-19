#pragma onve
#include "../IDataOperations.h"
#include "NodeBTree.h"
namespace s21 {
template <typename Key, typename Value>
class Btree : public IDataOperations<Key, Value> {
    //           OVERRIDE IDATAOPERATION METHODS
 public:
    void SET(const Key& key, const Value& value) final {
        if (rootIsNull()) {
            root = new NodeBtree<Key, Value>(level, TypeOfNode::LEAF);
            root.
        } else {
            if (root->isCompleted()) {
                NodeBtree<Key,Value>* tmpNode = new NodeBtree<Key, Value>(level, TypeOfNode::ROOT);
                tmpNode->getDescendent(0)=root;
                tmpNode->insert(root);
                int index=0;
                if(tmpNode.)
            } else {
                root->insert(key, value);
            }
        }
    }
    // Value GET(const Key&) final {}
    // bool EXISTS(const Key&) final {}
    // bool DEL(const Key&) final {}
    // void UPDATE(const Key&, const Value&) final {}
    // std::vector<Key> KEYS() final {}
    // void RENAME(const Key&, const Key&) final {}
    // void TTL(const Key&) final {}
    // std::vector<Key> FIND(const Value&) final {}
    // void SHOWALL() final {}
    // void UPLOAD(const std::string&) final {}
    // void EXPORT(const std::string&) final {}
    //            CONSTRUCTORS AND DESTRUCTORS
 public:
    Btree() = delete;
    Btree(int valueOfOrder) {
        if (valueOfOrder < MIN_ORDER_OF_NODE || valueOfOrder > MAX_ORDER_OF_NODE)
            throw std::invalid_argument("Unacceptable value for the BTree order!");
        level = valueOfOrder;
    }
    Btree(const Btree&) = delete;
    Btree(Btree&&) = delete;
    virtual ~Btree() {}
    //            SIMPLE FUNCTION
 public:
    int getOrder() { return level; }
    int rootIsNull() { return root == nullptr; }

 private:
    const static int MAX_ORDER_OF_NODE = 10000;
    const static int MIN_ORDER_OF_NODE = 2;
    int level;
    NodeBtree<Key, Value>* root;
};
}  // namespace s21
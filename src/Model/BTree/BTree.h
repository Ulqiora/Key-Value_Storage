#pragma onve
#include <algorithm>
#include <deque>
#include <ostream>
#include <string>

#include "../IDataOperations.h"
namespace s21 {

class BTree : public IDataOperations {
    using Key = std::string;
    using Value = DataS21Student;
    //           OVERRIDE IDATAOPERATION METHODS
   private:
    struct NodeBTree {
        bool isLeaf;
        int degree;
        std::deque<std::pair<Key, Value>*> keyValues;
        std::deque<NodeBTree*> descendants;
        NodeBTree() = delete;
        NodeBTree(int newDegree, bool leaf) : isLeaf(leaf), degree(newDegree) {}
        void insert(const Key&, const Value&);
        void splitDescendants(int indexDescendants, NodeBTree* splitedNode);
        bool nodeIsLeaf() { return isLeaf == true; }
        bool isFull() { return keyValues.size() == (degree * 2 - 1); }
        std::string toString();
        void printInfo(std::ofstream&);
        std::pair<Key, Value>* findValueByKey(const Key&);
    };

   public:
    BTree(int newlevel) {
        if (newlevel > MAX_ORDER_OF_NODE || newlevel < MIN_ORDER_OF_NODE)
            throw std::invalid_argument("Incorrect value in constructor!");
        degree = newlevel;
    }
    void SET(const Key& key, const Value& value) final;
    Value* GET(const Key&) final;
    bool EXISTS(const Key&) final;
    // bool DEL(const Key&) final {}
    void UPDATE(const Key&, const Value&) final;
    // std::vector<Key> KEYS() final {}
    // void RENAME(const Key&, const Key&) final {}
    // void TTL(const Key&) final {}
    // std::vector<Key> FIND(const Value&) final {}
    // void SHOWALL() final {}
    // void UPLOAD(const std::string&) final {}
    // void EXPORT(const std::string&) final {}
    //            CONSTRUCTORS AND DESTRUCTORS
    size_t sizeOfDescendants() { return root->descendants.size(); }
    void printToGraphViz(const std::string&);

   private:
    bool rootIsFull() { return root->keyValues.size() == (2 * degree - 1); }

   private:
    const static int MAX_ORDER_OF_NODE = 10000;
    const static int MIN_ORDER_OF_NODE = 2;
    int degree;
    NodeBTree* root;
};
}  // namespace s21
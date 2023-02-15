#pragma onve
#include <algorithm>
#include <deque>
#include <ostream>
#include <string>
#include <optional>
#include <exception>
#include <iomanip>
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
        std::pair<Key,Value>* findValueByKey(const Key&);
        std::vector<Key> getKeys();
        // delete
        void deletion(const Key& key);
        int findValueByKeyCurrNode(const Key& key);
        void removeFromLeaf(int index);
        void removeFromNotLeaf(int index);
        std::pair<Key, Value>** getPredecessor(int idx);
        std::pair<Key, Value>** getSuccessor(int idx);
        void fill(int idx);
        void borrowFromPrev(int idx);
        void borrowFromNext(int idx);
        void merge(int idx);
        // find
        std::vector<Key> findKeysByValue(const Value& value);
        // showall
        void printInfo(int& index);
        std::vector<DataS21Student> getAllValues();
        // export
        int printInfo(std::ofstream& file);
        // upload
        // void readInfo(std::ifstream& file);

        // dot
        void printToGraph(std::ofstream& file);
    };

   public:
    explicit BTree(int newlevel) {
        if (newlevel > MAX_ORDER_OF_NODE || newlevel < MIN_ORDER_OF_NODE)
            throw std::invalid_argument("Incorrect value in constructor!");
        degree = newlevel;
    }
    bool SET(const Key& key, const Value& value) final;
    std::optional<Value> GET(const Key&) final;
    bool EXISTS(const Key&) final;
    bool DEL(const Key&) final ;
    bool UPDATE(const Key&, const Value&) final;
    std::vector<Key> KEYS() final;
    bool RENAME(const Key& prev, const Key& updated) final {
        auto temp = *(root->findValueByKey(prev));
        DEL(prev);
        SET(updated,temp.second);
        return true;
    }
    // void TTL(const Key&) final {}
    std::vector<Key> FIND(const Value& value) final {
        auto temp = root->findKeysByValue(value);
        std::sort(temp.begin(),temp.end());
        return temp;
    }
    std::vector<DataS21Student> SHOWALL() final ;
    int UPLOAD(const std::string& filename) final;
    int EXPORT(const std::string&) final ;
    //            CONSTRUCTORS AND DESTRUCTORS
    size_t sizeOfDescendants() { return root->descendants.size(); }
    void printToGraphViz(const std::string&);
    virtual ~BTree(){}
   private:
    bool rootIsFull() { return root->keyValues.size() == (2 * degree - 1); }

   private:
    const static int MAX_ORDER_OF_NODE = 10000;
    const static int MIN_ORDER_OF_NODE = 2;
    int degree;
    NodeBTree* root=nullptr;
};
}  // namespace s21
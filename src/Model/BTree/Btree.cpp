#include "BTree.h"

namespace s21 {
//          SET
void BTree::SET(const Key& key, const Value& value) {
    // std::cout<<"set is start!";
    if (root == nullptr) {
        root = new NodeBTree(degree, true);
        root->keyValues.push_back(new std::pair<Key, Value>(key, value));
        root->descendants.push_back(nullptr);
        root->descendants.push_back(nullptr);
        return;
    }
    if (rootIsFull()) {
        NodeBTree* newRoot = new NodeBTree(degree, false);
        // std::cout<<"Split is start!";
        // while(1){}
        newRoot->descendants.push_back(root);
        // std::cout<<"Split is start!";
        newRoot->splitDescendants(0,root);
        // std::cout<<"Split is complete!";
        int i=0;
        if(newRoot->keyValues[0]->first < key) i++;
        newRoot->descendants[i]->insert(key,value);
        root=newRoot;
    } else {
        root->insert(key,value);
    }
}

void BTree::NodeBTree::insert(const Key& key, const Value& value){
    int indexRightestElem=keyValues.size()-1;
    if(nodeIsLeaf()){
        while (indexRightestElem >= 0 && keyValues[indexRightestElem]->first > key) indexRightestElem--;
        keyValues.insert(keyValues.begin() + indexRightestElem + 1, new std::pair<Key, Value>(key, value));
        descendants.insert(descendants.begin() + indexRightestElem + 1, nullptr);
    } else {
        while (indexRightestElem >= 0 && keyValues[indexRightestElem]->first > key) indexRightestElem--;
        if(descendants[indexRightestElem+1]->isFull()){
            splitDescendants(indexRightestElem+1,descendants[indexRightestElem+1]);
            if (keyValues[indexRightestElem + 1]->first < key) indexRightestElem++;
        } 
        descendants[indexRightestElem+1]->insert(key,value);
    }
}

void BTree::NodeBTree::splitDescendants(int indexDescendants, NodeBTree* splitedNode) {
    NodeBTree* z = new NodeBTree(splitedNode->degree, splitedNode->isLeaf);
    z->keyValues.resize(degree-1);
    std::copy(splitedNode->keyValues.begin()+degree,splitedNode->keyValues.end(),z->keyValues.begin());
    splitedNode->keyValues.erase(splitedNode->keyValues.begin() + degree, splitedNode->keyValues.end());
    if (!splitedNode->nodeIsLeaf()) {
        z->descendants.resize(degree);
        std::copy(splitedNode->descendants.begin()+degree,splitedNode->descendants.end(),z->descendants.begin());
        splitedNode->descendants.erase(splitedNode->descendants.begin() + degree, splitedNode->descendants.end());
    } else {
        splitedNode->descendants.resize(degree);
        z->descendants.resize(degree);
    }
    descendants.insert(descendants.begin() + indexDescendants+1,z);
    auto last = splitedNode->keyValues[degree-1];
    auto index = std::find_if(keyValues.begin(),keyValues.end(),[last](std::pair<Key,Value>* temp){return temp->first >= last->first; });
    keyValues.insert(index,last);
    splitedNode->keyValues.pop_back();
}

std::string BTree::NodeBTree::toString() {
    std::string temp("\"|");
    for (auto pairKV : keyValues) {
        temp += pairKV->first + "|";
    }
    return temp + std::to_string(descendants.size()) + "\"" ;
}

void BTree::NodeBTree::printInfo(std::ofstream& file) {
    for (auto descendant : descendants) {
        if (descendant != nullptr) {
            std::cout << toString();
            file << toString() << "->" << descendant->toString() << ";\n\t";
            std::cout << "         " << (descendant) << '\n';
            descendant->printInfo(file);
        }
        // if (descendant != nullptr) descendant->printInfo(file);
    }
}

void BTree::printToGraphViz(const std::string& filename ){
    std::ofstream file;
    file.open(filename,std::ofstream::out);
    if(file.is_open()){
        file<<"digraph { \n\t";
        root->printInfo(file);
        file<<" }";
        file.close();
    }
}

//         GET
std::optional<BTree::Value> BTree::GET(const Key& key){
    auto findedPair=root->findValueByKey(key);
    if(findedPair)
        return findedPair->second;
    return std::nullopt;
}

std::pair<BTree::Key, BTree::Value>* BTree::NodeBTree::findValueByKey(const Key& key){
    for (int i = 0; i < keyValues.size(); ++i) {
        if(keyValues[i]->first == key){
            return (keyValues[i]);
        } else if (keyValues[i]->first > key && descendants[i] != nullptr) {
            return descendants[i]->findValueByKey(key);
        } else if ((i == (keyValues.size() - 1)) && (keyValues[i]->first < key) && (descendants[i+1] != nullptr)){
            return descendants[i+1]->findValueByKey(key);
        }
    }
    return nullptr;
}
//          EXISTS
bool BTree::EXISTS(const Key& key){
    return root->findValueByKey(key)==nullptr;
}
//          UPDATE
void BTree::UPDATE(const Key& key, const Value& value) {
    std::pair<Key,Value>* findedPair=root->findValueByKey(key);
    if(findedPair!=nullptr) findedPair->second=value;
}
//          KEYS
std::vector<BTree::Key> BTree::KEYS(){
    return root->getKeys();
}
std::vector<BTree::Key> BTree::NodeBTree::getKeys(){
    std::vector<Key> result;
    if(isLeaf){
        result.reserve(keyValues.size());
        for(auto& curr_pair: keyValues){
            result.push_back(curr_pair->first);
        }
    } else {
        result.reserve(keyValues.size());
        for(int i=0;i<keyValues.size();i++){
            auto keysDescendents=descendants[i]->getKeys();
            for(auto& keysDescendent:keysDescendents){
                result.push_back(keysDescendent);
            }
            result.push_back(keyValues[i]->first);
        }
        auto keysDescendents=descendants[descendants.size()-1]->getKeys();
        for(auto& keysDescendent:keysDescendents){
            result.push_back(keysDescendent);
        }
    }
    return result;
}

}  // namespace s21
#include "BTree.h"
namespace s21{
//          SET
bool BTree::SET(const Key& key, const Value& value) {
    if (root == nullptr) {
        root = new NodeBTree(degree, true);
        root->keyValues.push_back(new std::pair<Key, Value>(key, value));
        root->descendants.push_back(nullptr);
        root->descendants.push_back(nullptr);
    } else if (rootIsFull()) {
        NodeBTree* newRoot = new NodeBTree(degree, false);
        newRoot->descendants.push_back(root);
        newRoot->splitDescendants(0,root);
        int i=0;
        if(newRoot->keyValues[0]->first < key) i++;
        newRoot->descendants[i]->insert(key,value);
        root=newRoot;
    } else {
        root->insert(key,value);
    }
    return true;
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

void BTree::printToGraphViz(const std::string& filename ){
    std::ofstream file;
    file.open(filename,std::ofstream::out);
    if(file.is_open()){
        file<<"digraph { \n\t";
        root->printToGraph(file);
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
bool BTree::UPDATE(const Key& key, const Value& value) {
    std::pair<Key,Value>* findedPair=root->findValueByKey(key);
    if(findedPair!=nullptr) findedPair->second=value;
    return findedPair!=nullptr;
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
//
bool BTree::RENAME(const Key& prev, const Key& updated) {
    auto ptr = root->findValueByKey(prev);
    if(!ptr) return false;
    if(!DEL(prev)) return false;
    SET(updated, ptr->second);
    return true;
}

//          DELETE

bool s21::BTree::DEL(const Key& key) {
    if(!root)
        throw std::invalid_argument("Error! This tree is empty!");
    try{
        root->deletion(key);
    } catch (...){
        return false;
    }
    // printToGraphViz("temp.dot");
    if(root->descendants.size()==0){
        NodeBTree* temp=root;
        if(root->isLeaf){
            root =nullptr;
        } else {
            root=root->descendants[0];
        }
        delete  temp;
    }
    // std::cout<<root->findValueByKeyCurrNode(key);
    return true;
}

int BTree::NodeBTree::findValueByKeyCurrNode(const Key& key){
  return std::find_if(keyValues.begin(),keyValues.end(),[&key](std::pair<Key,Value>* temp){ return temp->first>=key;})-keyValues.begin();
}

void BTree::NodeBTree::deletion(const Key& key){
    auto index=findValueByKeyCurrNode(key);
    std::cout<<index<<"      |";
    if(index<keyValues.size()&&keyValues[index]->first==key){
        if(isLeaf){
            removeFromLeaf(index);
        }else {
            removeFromNotLeaf(index);
        }
    }else {
        std::cout<<"Not found in this node!"<<'\n';
        if(isLeaf)
            throw std::invalid_argument("Error! The key "+key+" is does not exist in the tree!");
        if (descendants[index]->keyValues.size() < degree) {
            fill(index);
        }
        descendants[index]->deletion(key);
    }
}
void BTree::NodeBTree::removeFromLeaf(int index){
    delete keyValues[index];
    keyValues.erase(keyValues.begin()+index);
    descendants.erase(descendants.begin());
}
void BTree::NodeBTree::removeFromNotLeaf(int index){
    if(descendants[index]->keyValues.size() >= degree){
        auto pred= getPredecessor(index);
        std::swap(*pred,keyValues[index]);
        descendants[index]->deletion((*pred)->first);
    } else if(descendants[index+1]->keyValues.size() >= degree){
        auto succ=getSuccessor(index);
        std::swap(*succ,keyValues[index]);
        descendants[index+1]->deletion((*succ)->first);
    } else {
        auto temp= keyValues[index]->first;
        merge(index);
        descendants[index]->deletion(temp);
    }
}
std::pair<s21::BTree::Key, s21::BTree::Value>** BTree::NodeBTree::getPredecessor(int index){
    NodeBTree* cur= descendants[index];
    while(!cur->isLeaf){
        cur=cur->descendants[cur->keyValues.size()];
    }
    return &(cur->keyValues[cur->keyValues.size()-1]);
}
std::pair<s21::BTree::Key, s21::BTree::Value>** BTree::NodeBTree::getSuccessor(int index){
    NodeBTree* cur= descendants[index+1];
    while(!cur->isLeaf){
        cur=cur->descendants[0];
    }
    return &(cur->keyValues[0]);
}
void BTree::NodeBTree::fill(int index){
    if (index != 0 && descendants[index - 1]->keyValues.size() >= degree){
        std::cout<<"borrowFromPrev\n";
        borrowFromPrev(index);
    }else if (index != keyValues.size() && descendants[index + 1]->keyValues.size() >= degree){
        std::cout<<"borrowFromNext\n";
        borrowFromNext(index);
    }else {
        std::cout<<"merge\n";
        if (index != keyValues.size())
            merge(index);
        else
            merge(index - 1);
    }
}
void BTree::NodeBTree::borrowFromPrev(int index){
    NodeBTree *child = descendants[index];
    NodeBTree *sibling = descendants[index - 1];
    child->keyValues.push_front(keyValues[index-1]);
    if (child->isLeaf) {
        child->descendants.push_front(sibling->descendants.back());
        sibling->descendants.pop_back();
    }
    keyValues[index-1]=sibling->keyValues.back();
    sibling->keyValues.pop_back();
}
void BTree::NodeBTree::borrowFromNext(int index){
    NodeBTree *child = descendants[index];
    NodeBTree *sibling = descendants[index + 1];
    child->keyValues.push_back(keyValues[index]);
    if (child->isLeaf) {
        child->descendants.push_back(sibling->descendants.front());
        sibling->descendants.pop_front();
    }
    keyValues[index]=sibling->keyValues.front();
    sibling->keyValues.pop_front();

}
void BTree::NodeBTree::merge(int index){
    NodeBTree *child = descendants[index];
    NodeBTree *sibling = descendants[index + 1];
    child->keyValues.push_back(keyValues[index]);
    for(auto kv : sibling->keyValues){
        child->keyValues.push_back(kv);
    }
    if(!child->isLeaf){
        for(auto descendant: sibling->descendants)
            child->descendants.push_back(descendant);
    }
    keyValues.erase(keyValues.begin()+index);
    descendants.erase(descendants.begin()+index+1);
    
    delete sibling;
}
//          FIND
std::vector<BTree::Key> BTree::FIND(const Value& value) {
    auto temp = root->findKeysByValue(value);
    std::sort(temp.begin(), temp.end());
    return temp;
}
std::vector<BTree::Key> BTree::NodeBTree::findKeysByValue(const Value& value){
    std::vector<Key> result;
    for(auto kv:keyValues){
        if(kv->second==value) result.push_back(kv->first);
    }
    if (!isLeaf) {
        for (auto desc : descendants) {
            auto temp = desc->findKeysByValue(value);
            std::copy(temp.begin(), temp.end(), std::back_inserter(result));
        }
    }
    return result;
}
//          SHOWALL
std::vector<DataS21Student> BTree::SHOWALL() {
    if(!root) return std::vector<DataS21Student>();
    return root->getAllValues();
}

std::vector<DataS21Student> BTree::NodeBTree::getAllValues(){
    std::vector<DataS21Student> result;
    for(int i=0;i<keyValues.size();i++){
        if (!isLeaf) {
            auto temp = std::move(descendants[i]->getAllValues());
            result.insert(result.end(),temp.begin(),temp.end());
        }
        result.push_back(keyValues[i]->second);
    }
    if (!isLeaf) {
        auto temp = std::move(descendants.back()->getAllValues());
        result.insert(result.end(),temp.begin(),temp.end());
    }
    return result;
}

void BTree::NodeBTree::printInfo(int& index){
    for(int i=0;i<keyValues.size();i++){
        if(!isLeaf) descendants[i]->printInfo(index);
        std::cout<<std::setw(4)<<index++<<keyValues[i]->second<<'\n';
    }
    if(!isLeaf) descendants.back()->printInfo(index);
}
//          EXPORT
int BTree::EXPORT(const std::string& filename){
    std::ofstream file(filename);
    if(file.is_open()){
        int res{0};
        if(root){
            res+=root->printInfo(file);
        }
        file.close();
        return res;
    }
    return 0;
}
int BTree::NodeBTree::printInfo(std::ofstream& file) {
    int result=0;
    for(int i=0;i<keyValues.size();i++){
        if(!isLeaf) result+=descendants[i]->printInfo(file);
        file<<std::left<<std::setw(10)<<keyValues[i]->first<<keyValues[i]->second<<'\n';
        result++;
    }
    if(!isLeaf) result+=descendants.back()->printInfo(file);
    return result;
}
//          UPLOAD
int BTree::UPLOAD(const std::string& filename) {
    std::ifstream file(filename);
    if(!file.is_open()){
        throw std::invalid_argument("This file "+filename+" is not opened!");

    }
    Value tempValue;
    Key tempKey;
    std::string currline;
    int i=0;
    while(std::getline(file,currline)){
        std::stringstream currLineStream{currline};
        currLineStream>>tempKey;
        currLineStream>>tempValue;
        SET(tempKey,tempValue);
        i++;
    }
    file.close();
    return i;
}

// dot
void BTree::NodeBTree::printToGraph(std::ofstream& file){
    for (auto descendant : descendants) {
        if (descendant != nullptr) {
            std::cout << toString();
            file << toString() << "->" << descendant->toString() << ";\n\t";
            std::cout << "         " << (descendant) << '\n';
            descendant->printToGraph(file);
        }
    }
}

}  // namespace s21
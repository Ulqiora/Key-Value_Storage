#pragma once
#include "../IDataOperations.h"
namespace s21{

template<typename Key, typename Value>
class HashTable: public IDataOperations<Key,Value>{
    struct HashTableTrio{
        Key key;
        Value value;
        std::chrono::seconds lifeTime;
    };
public:
    virtual void SET(const Key&,const Value&) final ;
    virtual Value GET(const Key&) final ;
    virtual bool EXISTS(const Key&) final ;
    virtual bool DEL(const Key&) final ;
    virtual void UPDATE(const Key&,const Value&) final ;
    virtual std::vector<Key> KEYS() final ;
    virtual void RENAME(const Key&,const Key&) final ;
    virtual void TTL(const Key&) final ;
    virtual std::vector<Key> FIND(const Value&) final ;
    virtual void SHOWALL()  final ;
    virtual void UPLOAD(const std::string&) final ;
    virtual void EXPORT(const std::string&) final ;
private:
    std::vector<Key> keys;
    std::vector<> 
};

}
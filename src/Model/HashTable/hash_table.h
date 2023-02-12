#pragma once
#include "../IDataOperations.h"
namespace s21 {

template <typename Key, typename Value>
class HashTable : public IDataOperations<Key, Value> {
    struct HashTableTrio {
        Key key;
        Value value;
    };

   public:
    virtual void SET(const Key& key, const Value& value) final {
        struct hashtabletrio {
            Key key;
            Value value;
            hashtabletrio* next;
        };
        std::vector<hashtabletrio*> hash_data_;
        hashtabletrio* temp = new hashtabletrio(key, value, nullptr);
        int hash = hashFunction(key);
        if (hash_data_.size() < hash) hash_data_.resize(hash + 1);
        hashtabletrio* find = hash_data_[hash];
        if (hash_data_[hash])
            while (find) find = find->next;
        find = temp;

        // get
        hashtabletrio* find = hash_data_[hash];
        while (find.key != key) find = find->next;
    }
    virtual Value GET(const Key&) final;
    virtual bool EXISTS(const Key&) final;
    virtual bool DEL(const Key&) final;
    virtual void UPDATE(const Key&, const Value&) final;
    virtual std::vector<Key> KEYS() final;
    virtual void RENAME(const Key&, const Key&) final;
    virtual void TTL(const Key&) final;
    virtual std::vector<Key> FIND(const Value&) final;
    virtual void SHOWALL() final;
    virtual void UPLOAD(const std::string&) final;
    virtual void EXPORT(const std::string&) final;

   private:
};

}  // namespace s21
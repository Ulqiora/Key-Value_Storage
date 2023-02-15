#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <chrono>
#include <optional>

#include "DataS21Student.h"
namespace s21{

class IDataOperations{
public:
    using Key = std::string;
    using Value = DataS21Student;
    virtual bool SET(const Key&,const Value&)=0;
    virtual std::optional<Value> GET(const Key&)=0;
    virtual bool EXISTS(const Key&)=0;
    virtual bool DEL(const Key&)=0;
    virtual bool UPDATE(const Key&,const Value&)=0;
    virtual std::vector<Key> KEYS()=0;
    virtual bool RENAME(const Key&,const Key&)=0;
    // virtual int TTL(const Key&)=0;
    virtual std::vector<Key> FIND(const Value&)=0;
    virtual std::vector<DataS21Student> SHOWALL() =0;
    virtual int UPLOAD(const std::string& filename)=0;
    virtual int EXPORT(const std::string&)=0;
    virtual ~IDataOperations(){}
};

}

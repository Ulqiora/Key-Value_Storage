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
    virtual void SET(const Key&,const Value&)=0;
    virtual std::optional<Value> GET(const Key&)=0;
    virtual bool EXISTS(const Key&)=0;
    virtual bool DEL(const Key&)=0;
    virtual void UPDATE(const Key&,const Value&)=0;
    virtual std::vector<Key> KEYS()=0;
    virtual void RENAME(const Key&,const Key&)=0;
    // virtual void TTL(const Key&)=0;
    virtual std::vector<Key> FIND(const Value&)=0;
    virtual void SHOWALL() =0;
    virtual void UPLOAD(const std::string& filename)=0;
    virtual void EXPORT(const std::string&)=0;
    virtual ~IDataOperations(){}
};

}

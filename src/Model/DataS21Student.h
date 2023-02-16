#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <regex>

namespace s21 {
bool CheckStruct(const std::string& data);

class DataS21Student {
 public:
    DataS21Student() = default;
    DataS21Student(const std::string&, const std::string&, int, const std::string&, int);
    DataS21Student(const DataS21Student&);
    std::string toStdString() const;
   bool operator==(const DataS21Student&)const;
   DataS21Student& operator=(const DataS21Student&);
 public:
    std::string getFirstname();
    std::string getLastname();
    std::string getCity();
    int getYear();
    int getCoins();
    void setFirstname(const std::string&);
    void setLastname(const std::string&);
    void setCity(const std::string&);
    void setYear(int);
    void setCoins(int);
    void initThisHyphen(const std::string&);
 private:
    std::string firstname;
    std::string lastname;
    int birthYear;
    std::string city;
    int numOfCoins;
};

std::ostream& operator<<(std::ostream& os, DataS21Student& entry);
std::ofstream& operator<<(std::ofstream& ofs, DataS21Student& entry);
std::istream& operator>>(std::istream& is, DataS21Student& entry);
std::ifstream& operator>>(std::ifstream& ifs, DataS21Student& entry);

}  // namespace s21
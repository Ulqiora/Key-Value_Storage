#pragma once
#include <fstream>
#include <iostream>
#include <string>
namespace s21 {

struct DataS21Student {
    DataS21Student() = delete;
    DataS21Student(const std::string&, const std::string&, int, const std::string&, int);
    DataS21Student(const DataS21Student&);
    std::string toStdString() const;

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
   private:
    std::string firstname;
    std::string lastname;
    int birthYear;
    std::string city;
    int numOfCoins;
};

std::ostream& operator<<(std::ostream& os, DataS21Student& entry);
std::ofstream& operator<<(std::ofstream& ofs, DataS21Student& entry);
std::istream& operator>>(std::istream& is,DataS21Student& entry);
std::ifstream& operator>>(std::ifstream& ifs,DataS21Student& entry);

}  // namespace s21
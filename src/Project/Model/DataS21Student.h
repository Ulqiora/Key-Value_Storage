#pragma once

#include <fstream>
#include <iomanip>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

namespace s21 {
class DataS21Student {
 public:
  DataS21Student() = default;
  DataS21Student(const std::string& newLastname,
                 const std::string& newFirstname, int newYear,
                 const std::string& newCity, int newCoins);
  DataS21Student(const DataS21Student&);
  DataS21Student(DataS21Student&& other) { (*this) = std::move(other); }
  ~DataS21Student() {}
  DataS21Student& operator=(const DataS21Student&);
  bool operator==(const DataS21Student&) const;
  bool operator<(const DataS21Student&) const;
  std::string ToStdString() const;

 public:
  std::string GetFirstname() const;
  std::string GetLastname() const;
  std::string GetCity() const;
  int GetYear() const;
  int GetCoins() const;
  void SetFirstname(const std::string&);
  void SetLastname(const std::string&);
  void SetCity(const std::string&);
  void SetYear(int);
  void SetCoins(int);
  void InitThisHyphen(std::stringstream&);

 private:
  std::string lastname_;
  std::string firstname_;
  int birth_year_;
  std::string city_;
  int num_of_coins_;
};

std::ostream& operator<<(std::ostream& os, const DataS21Student& entry);
std::ofstream& operator<<(std::ofstream& ofs, const DataS21Student& entry);
std::istream& operator>>(std::istream& is, DataS21Student& entry);
std::ifstream& operator>>(std::ifstream& ifs, DataS21Student& entry);

bool CheckStruct(std::string& data);

}  // namespace s21

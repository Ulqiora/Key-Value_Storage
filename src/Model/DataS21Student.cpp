#include "DataS21Student.h"
namespace s21 {
DataS21Student::DataS21Student(const std::string& newFirstname, const std::string& newLastname, int newYear,
                               const std::string& newCity, int newCoins)
    : firstname(newFirstname),
      lastname(newLastname),
      birthYear(newYear),
      city(newCity),
      numOfCoins(newCoins) {}

DataS21Student::DataS21Student(const DataS21Student& other)
    : firstname(other.firstname),
      lastname(other.lastname),
      birthYear(other.birthYear),
      city(other.city),
      numOfCoins(other.numOfCoins) {}

std::string DataS21Student::toStdString() const {
    std::string result;
    return lastname + " " + firstname + " " + std::to_string(birthYear) + " " + city + " " +
           std::to_string(numOfCoins);
}
void DataS21Student::initFromStdStr(const std::string& initStr){
    std::stringstream ss(initStr);
    ss >> lastname >> firstname >> birthYear >> city >> numOfCoins;
}

void DataS21Student::setFirstname(const std::string& str) { firstname = str; }
void DataS21Student::setLastname(const std::string& str) { lastname = str; }
void DataS21Student::setCity(const std::string& str) { city = str; }
void DataS21Student::setYear(int value) { birthYear = value; }
void DataS21Student::setCoins(int value) { numOfCoins = value; }
std::string DataS21Student::getFirstname(){return firstname;}
std::string DataS21Student::getLastname(){return lastname;}
std::string DataS21Student::getCity(){return city;}
int DataS21Student::getYear(){return birthYear;}
int DataS21Student::getCoins(){return numOfCoins;}

std::ostream& operator<<(std::ostream& os, DataS21Student& entry) {
    os << entry.toStdString();
    return os;
}
std::ofstream& operator<<(std::ofstream& ofs, DataS21Student& entry) {
    ofs << entry.toStdString();
    return ofs;
}

std::istream& operator>>(std::istream& is, DataS21Student& entry) {
    std::string tempstring;
    int tempint;
    is >> tempstring, entry.setFirstname(tempstring);
    is >> tempstring, entry.setLastname(tempstring);
    is >> tempint, entry.setYear(tempint);
    is >> tempstring, entry.setLastname(tempstring);
    is >> tempint, entry.setCoins(tempint);
    return is;
}

std::ifstream& operator>>(std::ifstream& ifs, DataS21Student& entry) {
    std::string tempstring;
    int tempint;
    ifs >> tempstring, entry.setFirstname(tempstring);
    ifs >> tempstring, entry.setLastname(tempstring);
    ifs >> tempint, entry.setYear(tempint);
    ifs >> tempstring, entry.setLastname(tempstring);
    ifs >> tempint, entry.setCoins(tempint);
    return ifs;
}

bool DataS21Student::operator==(const DataS21Student& other) const {
    if(other.birthYear!=birthYear) return false;
    if(other.firstname!=firstname) return false;
    if(other.lastname!=lastname) return false;
    if(other.city!=city) return false;
    if(other.numOfCoins!=numOfCoins) return false;
    return true;
}

DataS21Student& DataS21Student::operator=(const DataS21Student& other){
  if (other.firstname != "-") firstname = other.firstname;
  if (other.lastname != "-") lastname = other.lastname;
  if (other.birthYear != 0) birthYear = other.birthYear;
  if (other.city != "-") city = other.city;
  if (other.numOfCoins != -1) numOfCoins = other.numOfCoins;
  return *this;
}

}  // namespace s21
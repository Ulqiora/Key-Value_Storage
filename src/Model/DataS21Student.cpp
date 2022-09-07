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
    return firstname + " " + lastname + " " + std::to_string(birthYear) + " " + city + " " +
           std::to_string(numOfCoins);
}

void DataS21Student::setFirstname(const std::string& str) { firstname = str; }
void DataS21Student::setLastname(const std::string& str) { lastname = str; }
void DataS21Student::setCity(const std::string& str) { city = str; }
void DataS21Student::setYear(int value) { birthYear = value; }
void DataS21Student::setCoins(int value) { numOfCoins = value; }

std::ostream& operator<<(std::ostream& os, DataS21Student& entry) {
    os << entry.toStdString();
    return os;
}
std::ofstream& operator<<(std::ofstream& ofs, DataS21Student& entry) {
    ofs << entry.toStdString();
    return ofs;
}

std::istream& operator>>(std::istream& is,DataS21Student& entry){
    std::string tempstring;
    int tempint;
    is>>tempstring, entry.setFirstname(tempstring);
    is>>tempstring, entry.setLastname(tempstring);
    is>>tempint, entry.setYear(tempint);
    is>>tempstring, entry.setLastname(tempstring);
    is>>tempint, entry.setCoins(tempint);
    return is;
}

std::ifstream& operator>>(std::ifstream& ifs,DataS21Student& entry){
    std::string tempstring;
    int tempint;
    ifs>>tempstring, entry.setFirstname(tempstring);
    ifs>>tempstring, entry.setLastname(tempstring);
    ifs>>tempint, entry.setYear(tempint);
    ifs>>tempstring, entry.setLastname(tempstring);
    ifs>>tempint, entry.setCoins(tempint);
    return ifs;
}

}  // namespace s21
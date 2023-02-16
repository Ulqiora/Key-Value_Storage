#include "DataS21Student.h"
namespace s21 {

bool CheckStruct(const std::string& data) {
  const std::regex pattern(
      "\\s+?(\\w+)\\s+(\\w+(-\\w+)?)\\s+(\\w+(-\\w+)?)\\s+(\\d{4})\\s+(\\w+(-"
      "\\w+)?)\\s+(\\d+)(\\s+EX\\s+\\d+)?");

  return (!data.empty() && regex_match(data, pattern));
}


DataS21Student::DataS21Student(const std::string& newLastname,const std::string& newFirstname, int newYear,
                               const std::string& newCity, int newCoins)
    : lastname(newLastname),
      firstname(newFirstname),
      birthYear(newYear),
      city(newCity),
      numOfCoins(newCoins) {}

DataS21Student::DataS21Student(const DataS21Student& other)
    : lastname(other.lastname),
      firstname(other.firstname),
      birthYear(other.birthYear),
      city(other.city),
      numOfCoins(other.numOfCoins) {}

std::string DataS21Student::toStdString() const {
    return " \"" + lastname + "\" \"" + firstname + "\" " +
            std::to_string(birthYear) + " \"" + city + "\" " +
            std::to_string(numOfCoins);
}
void DataS21Student::initThisHyphen(const std::string& initStr){
    std::stringstream ss(initStr);
    std::string temp;
    ss >> lastname >> firstname;
    ss >> temp, birthYear = (temp == "-" ? -1 : std::stoi(temp));
    ss >> city;
    ss >> temp, numOfCoins = (temp == "-" ? -1 : std::stoi(temp));
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
    os  <<std::left<< std::setw(15)    <<entry.getLastname()
        <<std::left<< std::setw(15)    <<entry.getFirstname()
        <<std::left<< std::setw(8)     <<  std::to_string(entry.getYear())
        <<std::left<< std::setw(15)    << entry.getCity()
        <<std::left<< std::setw(8)     <<entry.getCoins();
    return os;
}
std::ofstream& operator<<(std::ofstream& ofs, DataS21Student& entry) {
    ofs  <<std::left<< std::setw(15)    <<" \"" + entry.getLastname() + "\"" 
        <<std::left<< std::setw(15)    <<" \"" + entry.getFirstname() + "\" "
        <<std::left<< std::setw(8)     <<  std::to_string(entry.getYear())
        <<std::left<< std::setw(15)    << " \"" + entry.getCity() + "\" "
        <<std::left<< std::setw(8)     <<entry.getCoins();
    return ofs;
}

std::istream& operator>>(std::istream& is, DataS21Student& entry) {
    std::string tempstring;
    int tempint;
    is >> tempstring, entry.setLastname(tempstring);
    is >> tempstring, entry.setFirstname(tempstring);
    is >> tempint, entry.setYear(tempint);
    is >> tempstring, entry.setCity(tempstring);
    is >> tempint, entry.setCoins(tempint);
    return is;
}

std::ifstream& operator>>(std::ifstream& ifs, DataS21Student& entry) {
    std::string tempstring;
    int tempint;
    ifs >> tempstring, entry.setLastname(tempstring);
    ifs >> tempstring, entry.setFirstname(tempstring);
    ifs >> tempint, entry.setYear(tempint);
    ifs >> tempstring, entry.setCity(tempstring);
    ifs >> tempint, entry.setCoins(tempint);
    return ifs;
}

bool DataS21Student::operator==(const DataS21Student& other) const {
    if(!(other.birthYear==birthYear|| other.birthYear==-1 || birthYear==-1)) return false;
    if(!(other.firstname==firstname|| other.firstname=="-" || firstname=="-")) return false;
    if(!(other.lastname==lastname|| other.lastname=="-" || lastname=="-")) return false;
    if(!(other.city==city|| other.city=="-" || city=="-")) return false;
    if(!(other.numOfCoins==numOfCoins|| other.numOfCoins==-1 || numOfCoins==-1)) return false;
    return true;
}

DataS21Student& DataS21Student::operator=(const DataS21Student& other){
  if (other.firstname != "-") firstname = other.firstname;
  if (other.lastname != "-") lastname = other.lastname;
  if (other.birthYear != -1) birthYear = other.birthYear;
  if (other.city != "-") city = other.city;
  if (other.numOfCoins != -1) numOfCoins = other.numOfCoins;
  return *this;
}

}  // namespace s21
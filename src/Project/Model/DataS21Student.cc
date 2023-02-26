#include "DataS21Student.h"

namespace s21 {
DataS21Student::DataS21Student(const std::string &newLastname,
                               const std::string &newFirstname, int newYear,
                               const std::string &newCity, int newCoins)
    : lastname_(newLastname),
      firstname_(newFirstname),
      birth_year_(newYear),
      city_(newCity),
      num_of_coins_(newCoins) {}

DataS21Student::DataS21Student(const DataS21Student &other)
    : lastname_(other.lastname_),
      firstname_(other.firstname_),
      birth_year_(other.birth_year_),
      city_(other.city_),
      num_of_coins_(other.num_of_coins_) {}

std::string DataS21Student::ToStdString() const {
  return " \"" + lastname_ + "\" \"" + firstname_ + "\" " +
         std::to_string(birth_year_) + " \"" + city_ + "\" " +
         std::to_string(num_of_coins_);
}

void DataS21Student::InitThisHyphen(std::stringstream &ss) {
  std::string temp;
  ss >> lastname_ >> firstname_;
  ss >> temp, birth_year_ = (temp == "-" ? -1 : std::stoi(temp));
  ss >> city_;
  ss >> temp, num_of_coins_ = (temp == "-" ? -1 : std::stoi(temp));
}

void DataS21Student::SetFirstname(const std::string &str) { firstname_ = str; }
void DataS21Student::SetLastname(const std::string &str) { lastname_ = str; }
void DataS21Student::SetCity(const std::string &str) { city_ = str; }
void DataS21Student::SetYear(int value) { birth_year_ = value; }
void DataS21Student::SetCoins(int value) { num_of_coins_ = value; }
std::string DataS21Student::GetFirstname() const { return firstname_; }
std::string DataS21Student::GetLastname() const { return lastname_; }
std::string DataS21Student::GetCity() const { return city_; }
int DataS21Student::GetYear() const { return birth_year_; }
int DataS21Student::GetCoins() const { return num_of_coins_; }

std::ostream &operator<<(std::ostream &os, const DataS21Student &entry) {
  os << std::left << std::setw(15) << entry.GetLastname() << std::left
     << std::setw(14) << entry.GetFirstname() << std::left << std::setw(15)
     << std::to_string(entry.GetYear()) << std::left << std::setw(15)
     << entry.GetCity() << std::left << std::setw(8) << entry.GetCoins();
  return os;
}
std::ofstream &operator<<(std::ofstream &ofs, const DataS21Student &entry) {
  ofs << std::left << std::setw(15) << " \"" + entry.GetLastname() + "\""
      << std::left << std::setw(15) << " \"" + entry.GetFirstname() + "\" "
      << std::left << std::setw(8) << std::to_string(entry.GetYear())
      << std::left << std::setw(15) << " \"" + entry.GetCity() + "\" "
      << std::left << std::setw(8) << entry.GetCoins();
  return ofs;
}

std::istream &operator>>(std::istream &is, DataS21Student &entry) {
  std::string tempstring;
  int tempint;
  is >> tempstring, entry.SetLastname(tempstring);
  is >> tempstring, entry.SetFirstname(tempstring);
  is >> tempint, entry.SetYear(tempint);
  is >> tempstring, entry.SetCity(tempstring);
  is >> tempint, entry.SetCoins(tempint);
  return is;
}

std::ifstream &operator>>(std::ifstream &ifs, DataS21Student &entry) {
  std::string tempstring;
  int tempint;
  ifs >> tempstring, entry.SetLastname(tempstring);
  ifs >> tempstring, entry.SetFirstname(tempstring);
  ifs >> tempint, entry.SetYear(tempint);
  ifs >> tempstring, entry.SetCity(tempstring);
  ifs >> tempint, entry.SetCoins(tempint);
  return ifs;
}

bool DataS21Student::operator==(const DataS21Student &other) const {
  if (!(other.birth_year_ == birth_year_ || other.birth_year_ == -1 ||
        birth_year_ == -1))
    return false;
  if (!(other.firstname_ == firstname_ || other.firstname_ == "-" ||
        firstname_ == "-"))
    return false;
  if (!(other.lastname_ == lastname_ || other.lastname_ == "-" ||
        lastname_ == "-"))
    return false;
  if (!(other.city_ == city_ || other.city_ == "-" || city_ == "-"))
    return false;
  if (!(other.num_of_coins_ == num_of_coins_ || other.num_of_coins_ == -1 ||
        num_of_coins_ == -1))
    return false;
  return true;
}

DataS21Student &DataS21Student::operator=(const DataS21Student &other) {
  if (other.firstname_ != "-") firstname_ = other.firstname_;
  if (other.lastname_ != "-") lastname_ = other.lastname_;
  if (other.birth_year_ != -1) birth_year_ = other.birth_year_;
  if (other.city_ != "-") city_ = other.city_;
  if (other.num_of_coins_ != -1) num_of_coins_ = other.num_of_coins_;
  return *this;
}

bool DataS21Student::operator<(const DataS21Student &other) const {
  return (other.birth_year_ < birth_year_) ? true : false;
}

bool CheckStruct(std::string &data) {
  const std::regex pattern(
      "(\\s+)?(\\w+)\\s+(\\w+(-\\w+)?)\\s+(\\w+(-\\w+)?)\\s+(\\d{4})\\s+(\\w+(-"
      "\\w+)?)\\s+(\\d+)(\\s+EX\\s+\\d+)?");

  return (!data.empty() && regex_match(data, pattern));
}
}  // namespace s21

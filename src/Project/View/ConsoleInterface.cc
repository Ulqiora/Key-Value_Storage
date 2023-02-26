#include "ConsoleInterface.h"

void s21::ConsoleInterface::Init() {
  ChooseStore();
  InputCommand();
}

void s21::ConsoleInterface::ChooseStore() {
  std::cout << "Choose the store type:" << std::endl;
  std::cout << "1. Hash table" << std::endl;
  std::cout << "2. Self-balancing binary search tree" << std::endl;
  std::cout << "3. B+ tree" << std::endl;
  std::cout << "0. Exit" << std::endl;

  int num = CheckInput();
  if (num != -1 && num < 4) {
    if (num == 0) {
      std::cout << "The program is closed" << std::endl;
      exit(0);
    } else {
      SetStore(num);
    }
  } else {
    std::cout << "\nError: incorrect input, try again\n" << std::endl;
    ChooseStore();
  }
}

void s21::ConsoleInterface::SetStore(int num) {
  if (num == 1)
    controller_.SetHashTable();
  else if (num == 2)
    controller_.SelfBalancingBinarySearchTree();
  else if (num == 3)
    controller_.SetBTree();
}

void s21::ConsoleInterface::InputCommand() {
  std::cout << "\nEnter command" << std::endl;
  std::cout << "Use MANUAL for help" << std::endl;
  std::cout << "Type RESET to change the storage" << std::endl;
  std::cout << "Or input EXIT to exit the program" << std::endl;

  while (true) {
    std::string command, data;
    std::cout << std::endl;
    std::cin >> command;
    getline(std::cin, data);
    Command(command, data);
  }
}

void s21::ConsoleInterface::Manual() {
  std::cout << "\nSET command parameters:" << std::endl;
  std::cout << "SET <key> <Last name> <First name> <Year of birth> <City> "
               "<Number of current coins>"
            << std::endl;
  std::cout << "Or" << std::endl;
  std::cout << "SET <key> <Last name> <First name> <Year of birth> <City> "
               "<Number of current coins> EX <time in seconds>"
            << std::endl;

  std::cout << "\nGET command parameters:" << std::endl;
  std::cout << "GET <key>" << std::endl;

  std::cout << "\nEXISTS command parameters:" << std::endl;
  std::cout << "EXISTS <key>" << std::endl;

  std::cout << "\nDEL command parameters:" << std::endl;
  std::cout << "DEL <key>" << std::endl;

  std::cout << "\nUPDATE command parameters:" << std::endl;
  std::cout << "UPDATE <key> <Last name> <First name> <Year of birth> <City> <"
               "Number of current coins>"
            << std::endl;
  std::cout << "If there is a field that is not planned to change, it is "
               "replaced by a dash \"-\""
            << std::endl;

  std::cout << "\nRENAME command parameters:" << std::endl;
  std::cout << "RENAME <old key> <new key>" << std::endl;

  std::cout << "\nTTL command parameters:" << std::endl;
  std::cout << "TTL <key>" << std::endl;

  std::cout << "\nFIND command parameters:" << std::endl;
  std::cout << "FIND <Last name> <First name> <Year of birth> <City> <Number "
               "of current coins>"
            << std::endl;
  std::cout << "You don't have to specify all the values. If any fields will "
               "not be searched, it is replaced by a dash \"-\""
            << std::endl;

  std::cout << "\nUPLOAD command parameters:" << std::endl;
  std::cout << "UPLOAD <path to a file>" << std::endl;

  std::cout << "\nEXPORT command parameters:" << std::endl;
  std::cout << "EXPORT <path to a file>" << std::endl;
}

void s21::ConsoleInterface::Command(const std::string &command,
                                    std::string &data) {
  if (command == "EXIT") {
    std::cout << "The program is closed" << std::endl;
    exit(0);
  } else if (command == "RESET") {
    Init();
  } else if (command == "MANUAL") {
    Manual();
  } else if (command == "SET") {
    SetCommand(data);
  } else if (command == "GET") {
    GetCommand(data);
  } else if (command == "EXISTS") {
    ExistsCommand(data);
  } else if (command == "DEL") {
    DelCommand(data);
  } else if (command == "UPDATE") {
    UpdateCommand(data);
  } else if (command == "KEYS") {
    KeysCommand(data);
  } else if (command == "RENAME") {
    RenameCommand(data);
  } else if (command == "TTL") {
    TTLCommand(data);
  } else if (command == "FIND") {
    FindCommand(data);
  } else if (command == "SHOWALL") {
    ShowAllCommand(data);
  } else if (command == "UPLOAD") {
    UploadCommand(data);
  } else if (command == "EXPORT") {
    ExportCommand(data);
  } else {
    std::cout << "\nError: incorrect input, try again" << std::endl;
  }
}

void s21::ConsoleInterface::SetCommand(std::string &data) {
  if (CheckStruct(data)) {
    std::string key, skip;
    s21::DataS21Student value;
    std::stringstream ss(data);
    int seconds;
    ss >> key >> value;
    bool is_with_ex = !ss.eof();
    if (is_with_ex) ss >> skip >> seconds;
    std::chrono::seconds time(seconds);
    std::cout << (is_with_ex ? ((controller_.Set(key, value, time)
                                     ? "OK"
                                     : "The record is not inserted"))
                             : ((controller_.Set(key, value)
                                     ? "OK"
                                     : "The record is not inserted")))
              << std::endl;
  } else
    std::cout << "\nError: incorrect input, try again" << std::endl;
}

void s21::ConsoleInterface::GetCommand(std::string &data) {
  if (CheckKey(data)) {
    std::string key;
    std::stringstream ss(data);
    ss >> key;

    std::optional<s21::DataS21Student> res = controller_.Get(key);
    if (res.has_value())
      std::cout << res.value() << std::endl;
    else
      std::cout << "(null)" << std::endl;
  } else
    std::cout << "\nError: incorrect input, try again" << std::endl;
}

void s21::ConsoleInterface::ExistsCommand(std::string &data) {
  if (CheckKey(data)) {
    std::string key;
    std::stringstream ss(data);
    ss >> key;

    std::cout << (controller_.Exists(key) ? "true" : "false") << std::endl;
  } else
    std::cout << "\nError: incorrect input, try again" << std::endl;
}

void s21::ConsoleInterface::DelCommand(std::string &data) {
  if (CheckKey(data)) {
    std::string key;
    std::stringstream ss(data);
    ss >> key;

    std::cout << (controller_.Del(key) ? "true" : "false") << std::endl;
  } else
    std::cout << "\nError: incorrect input, try again" << std::endl;
}

void s21::ConsoleInterface::UpdateCommand(std::string &data) {
  if (CheckData(data)) {
    std::string key;
    s21::DataS21Student value;
    std::stringstream ss(data);
    ss >> key;
    value.InitThisHyphen(ss);

    std::cout << (controller_.Update(key, value) ? "OK"
                                                 : "The record is not updated")
              << std::endl;
  } else
    std::cout << "\nError: incorrect input, try again" << std::endl;
}

void s21::ConsoleInterface::KeysCommand(std::string &data) {
  if (!data.empty()) {
    std::cout << "\nError: incorrect input, try again" << std::endl;
  } else {
    std::vector<std::string> keys = controller_.Keys();
    if (!keys.empty()) {
      for (int i = 0; (size_t)i < keys.size(); ++i)
        std::cout << i + 1 << ") " << keys[i] << std::endl;
    } else {
      std::cout << "There are no keys in the storage" << std::endl;
    }
  }
}

void s21::ConsoleInterface::RenameCommand(std::string &data) {
  const std::regex pattern("\\s+?(\\w+)\\s+?(\\w+)");
  if (!data.empty() && regex_match(data, pattern)) {
    std::string key, new_key;
    std::stringstream ss(data);
    ss >> key >> new_key;

    std::cout << (controller_.Rename(key, new_key) ? "OK"
                                                   : "The key is not renamed")
              << std::endl;
  } else
    std::cout << "\nError: incorrect input, try again" << std::endl;
}

void s21::ConsoleInterface::TTLCommand(std::string &data) {
  if (CheckKey(data)) {
    std::string key;
    std::stringstream ss(data);
    ss >> key;

    int res = controller_.TTL(key);
    if (res != -1)
      std::cout << res << std::endl;
    else
      std::cout << "(null)" << std::endl;
  } else
    std::cout << "\nError: incorrect input, try again" << std::endl;
}

void s21::ConsoleInterface::FindCommand(std::string &data) {
  if (CheckStructure(data)) {
    s21::DataS21Student value;
    std::stringstream ss(data);
    value.InitThisHyphen(ss);

    std::optional<std::vector<std::string>> res = controller_.Find(value);
    if (res.has_value()) {
      for (int i = 0; (size_t)i < res.value().size(); ++i)
        std::cout << i + 1 << ") " << res.value()[i] << std::endl;
    } else {
      std::cout << "Nothing was found" << std::endl;
    }
  } else
    std::cout << "\nError: incorrect input, try again" << std::endl;
}

void s21::ConsoleInterface::ShowAllCommand(std::string &data) {
  if (!data.empty()) {
    std::cout << "\nError: incorrect input, try again" << std::endl;
  } else {
    std::vector<s21::DataS21Student> res = controller_.Showall();

    if (!res.empty()) {
      std::cout << std::left << std::setw(3) << "№   " << std::left
                << std::setw(15) << "|Last name" << std::left << std::setw(14)
                << "|First name" << std::left << std::setw(15) << "|Birthday"
                << std::left << std::setw(15) << "|City" << std::left
                << std::setw(8) << "|Coins"
                << "|\n";
      for (int i = 0; (size_t)i < res.size(); ++i) {
        std::cout << std::setw(5) << i + 1 << res[i] << '\n';
      }
    } else
      std::cout << "There are no records in the storage" << std::endl;
  }
}

void s21::ConsoleInterface::UploadCommand(std::string &data) {
  std::stringstream ss(data);
  std::filesystem::path way;
  ss >> way;

  if (!ss.eof()) {
    std::cout << "\nError: incorrect input, try again" << std::endl;
  } else {
    try {
      int counter = controller_.Upload(way);
      if (counter != 0)
        std::cout << "OK " << counter << std::endl;
      else
        std::cout << "No record was uploaded" << std::endl;
    } catch (const std::exception &e) {
      std::cerr << e.what() << std::endl;
    }
  }
}

void s21::ConsoleInterface::ExportCommand(std::string &data) {
  std::stringstream ss(data);
  std::filesystem::path way;
  ss >> way;

  if (!ss.eof()) {
    std::cout << "\nError: incorrect input, try again" << std::endl;
  } else {
    try {
      int counter = controller_.Export(way);
      if (counter != 0)
        std::cout << "OK " << counter << std::endl;
      else
        std::cout << "No record was exported" << std::endl;
    } catch (const std::exception &e) {
      std::cerr << e.what() << std::endl;
    }
  }
}

int s21::ConsoleInterface::CheckInput() {
  std::string choice;
  int num;
  std::cin >> choice;

  return IsNumber(choice) == 1 ? num = std::stoi(choice) : -1;
}

bool s21::ConsoleInterface::IsNumber(std::string choice) {
  bool result = true;
  for (std::string::size_type i = 0; i < choice.size(); ++i) {
    if (!std::isdigit(choice[i])) {
      result = false;
      break;
    }
  }
  return result;
}

bool s21::ConsoleInterface::CheckKey(std::string &data) {
  const std::regex pattern("\\s+?(\\w+)");
  return (!data.empty() && regex_match(data, pattern));
}

bool s21::ConsoleInterface::CheckData(std::string &data) {
  const std::regex pattern(
      "\\s+?(\\w+|-)\\s+(\\w+(-\\w+)?|-)\\s+(\\w+(-\\w+)?|-)\\s+(\\d{4}|-)\\s+("
      "\\w+(-\\w+)?|-)\\s+(\\d+|-)");
  return (!data.empty() && regex_match(data, pattern));
}

bool s21::ConsoleInterface::CheckStructure(std::string &data) {
  const std::regex pattern(
      "\\s+?(\\w+(-\\w+)?|-)\\s+(\\w+(-\\w+)?|-)\\s+(\\d{4}|-)\\s+("
      "\\w+(-\\w+)?|-)\\s+(\\d+|-)");
  return (!data.empty() && regex_match(data, pattern));
}

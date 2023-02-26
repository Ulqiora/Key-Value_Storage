#pragma once

#include "../Controller.h"

namespace s21 {
class ConsoleInterface {
 public:
  void Init();

 private:
  Controller controller_;

  void ChooseStore();
  void SetStore(int num);
  void InputCommand();
  void Command(const std::string& command, std::string& data);
  void Manual();
  void SetCommand(std::string& data);
  void GetCommand(std::string& data);
  void ExistsCommand(std::string& data);
  void DelCommand(std::string& data);
  void UpdateCommand(std::string& data);
  void KeysCommand(std::string& data);
  void RenameCommand(std::string& data);
  void TTLCommand(std::string& data);
  void FindCommand(std::string& data);
  void ShowAllCommand(std::string& data);
  void UploadCommand(std::string& data);
  void ExportCommand(std::string& data);
  int CheckInput();
  bool IsNumber(std::string choice);
  bool CheckKey(std::string& data);
  bool CheckData(std::string& data);
  bool CheckStructure(std::string& data);
};
}  // namespace s21

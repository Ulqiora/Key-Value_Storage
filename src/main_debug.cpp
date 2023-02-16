#include <filesystem>
#include <iostream>
#include <tuple>

#include "Model/BTree/BTree.h"
int main() {
    using namespace s21;
    DataS21Student data1("Ivanov", "Ivan", 2021, "hgkew", 234), data2;
    data2.initThisHyphen("Ivanov Ivan - - -");
    std::cout << data1.getLastname() + "   " + data2.getLastname() + "\n";
    std::cout << data1.getFirstname() + "   " + data2.getFirstname() + "\n";
    std::cout << (data1 == data2);
    return 0;
}

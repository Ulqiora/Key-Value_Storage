#include <iostream>
#include <tuple>

#include "Model/BTree/BTree.h"
int main() {
    s21::BTree temp(2);
    std::cout<<temp.UPLOAD("temp.txt")<<'\n';
    // temp.SHOWALL();
    // temp.SET("10", {"fsda", "fdsa", 22, "fdas", 21});
    // temp.SET("12", {"fsda", "fdsa", 22, "fdas", 22});
    // temp.SET("15", {"fsda", "fdsa", 22, "fdas", 23});
    // temp.SET("20", {"fsda", "fdsa", 22, "fdas", 24});
    // temp.SET("30", {"fsda", "fdsa", 22, "fdas", 25});
    // temp.SET("90", {"fsda", "fdsa", 22, "fdas", 25});
    // temp.SET("40", {"fsda", "fdsa", 22, "fdas", 26});
    // temp.SET("55", {"fsda", "fdsa", 22, "fdas", 27});
    // temp.SET("60", {"fsda", "fdsa", 22, "fdas", 27});
    // temp.SET("25", {"fsda", "fdsa", 22, "fdas", 21});
    // temp.SET("43", {"fsda", "fdsa", 22, "fdas", 21});
    // temp.SET("89", {"fsda", "fdsa", 22, "fdas", 21});
    // std::cout<<temp.EXPORT("temp.txt")<<'\n';
    // std::cout<<"----------------------------------------------------\n";
    auto res=temp.SHOWALL();
    for(auto& data: res){
      std::cout<<data<<'\n';
    }
    // temp.printToGraphViz("test.dot");
    // std::string temp1{" fdsafdsa Ivanov Ivan 2022 Ivanovo 234"}, key{""};
    // s21::DataS21Student data;
    // std::stringstream ss(temp1);
    // ss >> key >> data;
    // std::cout << data << "     " << key << '\n';
    return 0;
}

// #include "Model/BTree/BTree.h"
#include <fstream>
#include <string>

#include "Model/DataS21Student.h"
#include "Model/BTree/NodeBTree.h"
int main() {
    // int t=6;
    // std::vector<int> f{1,5,2,7};
    // auto res=std::find_if(f.begin(),f.end(),[t](int i){return t<i;});
    // std::cout<<(*res)<<"\n";
    // std::string initstr("Andrey Damdinov 2001 NSK 103");
    // std::ofstream f("kuku.txt");
    // s21::DataS21Student fds;
    // fds.initFromStdStr(initstr);
    // std::cout << fds << '\n';
    s21::NodeBtree<int,double,3> my;
    std::cout<<my.getLevel()<<'\n';
    return 0;
}
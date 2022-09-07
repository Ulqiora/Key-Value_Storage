// #include "Model/BTree/BTree.h"
#include "Model/DataS21Student.h"
#include <fstream>
#include <string>
int main(){
    // int t=6;
    // std::vector<int> f{1,5,2,7};
    // auto res=std::find_if(f.begin(),f.end(),[t](int i){return t<i;});
    // std::cout<<(*res)<<"\n";
    std::ofstream f("kuku.txt");
    s21::DataS21Student fds("Andrey","Damdinov",2001,"NSK",103);
    std::cout<<fds;
    return 0;
}
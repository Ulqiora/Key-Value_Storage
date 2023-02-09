#include <iostream>
#include "Model/BTree/BTree.h"

int main(){
  s21::IDataOperations* temp = new s21::BTree(2);
  s21::BTree tree(2);
  tree.SET("10", {"fsda", "fdsa", 22, "fdas", 21});
  tree.SET("12", {"fsda", "fdsa", 22, "fdas", 22});
  tree.SET("15", {"fsda", "fdsa", 22, "fdas", 23});
  tree.SET("20", {"fsda", "fdsa", 22, "fdas", 24});
  tree.SET("30", {"fsda", "fdsa", 22, "fdas", 25});
  tree.SET("40", {"fsda", "fdsa", 22, "fdas", 26});
  tree.SET("55", {"fsda", "fdsa", 22, "fdas", 27});
  tree.SET("60", {"fsda", "fdsa", 22, "fdas", 27});
  tree.SET("25", {"fsda", "fdsa", 22, "fdas", 21});
  tree.SET("43", {"fsda", "fdsa", 22, "fdas", 21});
  tree.SET("89", {"fsda", "fdsa", 22, "fdas", 21});
  // auto result=tree.GET("fe").value();
  // auto res=tree.KEYS();
  // for(auto i:res){
  //   std::cout<<i<<' ';
  // }
  tree.printToGraphViz("Test.dot");
  // tree.SET("foo",{"fsda","fdsa",22,"fdas",23});
  tree.DEL("20");
  // std::cout<<"\n-----------------------------------\n";
  // tree.DEL("90");
  // tree.DEL("20");
  tree.printToGraphViz("Test1.dot");
  return 0;
}
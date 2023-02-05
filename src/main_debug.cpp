#include <iostream>
#include "Model/BTree/BTree.h"

int main(){
  s21::BTree tree(2);
  tree.SET("fa", {"fsda", "fdsa", 22, "fdas", 21});
  tree.SET("fb", {"fsda", "fdsa", 22, "fdas", 22});
  tree.SET("fc", {"fsda", "fdsa", 22, "fdas", 23});
  tree.SET("fd", {"fsda", "fdsa", 22, "fdas", 24});
  tree.SET("fe", {"fsda", "fdsa", 22, "fdas", 25});
  tree.SET("fg", {"fsda", "fdsa", 22, "fdas", 26});
  tree.SET("fh", {"fsda", "fdsa", 22, "fdas", 27});
  tree.SET("fi", {"fsda", "fdsa", 22, "fdas", 27});
  tree.SET("fk", {"fsda", "fdsa", 22, "fdas", 27});
  tree.SET("fl", {"fsda", "fdsa", 22, "fdas", 27});
  tree.SET("fr", {"fsda", "fdsa", 22, "fdas", 28});
  tree.SET("fx", {"fsda", "fdsa", 22, "fdas", 29});
  tree.SET("fy", {"fsda", "fdsa", 22, "fdas", 29});
  tree.SET("fz", {"fsda", "fdsa", 22, "fdas", 29});
  tree.SET("fza", {"fsda", "fdsa", 22, "fdas", 29});
  tree.SET("fzb", {"fsda", "fdsa", 22, "fdas", 29});
  tree.SET("fzc", {"fsda", "fdsa", 22, "fdas", 29});
  tree.SET("fzd", {"fsda", "fdsa", 22, "fdas", 29});
  tree.SET("fze", {"fsda", "fdsa", 22, "fdas", 29});
  tree.SET("fzf", {"fsda", "fdsa", 22, "fdas", 29});
  tree.SET("fzg", {"fsda", "fdsa", 22, "fdas", 29});
  auto result=tree.GET("fe").value();
  auto res=tree.KEYS();
  for(auto i:res){
    std::cout<<i<<' ';
  }
  // std::cout<<tree.sizeOfDescendants()<<'\n';
  // tree.printToGraphViz("Test.dot");
  // tree.SET("foo",{"fsda","fdsa",22,"fdas",23});
  return 0;
}
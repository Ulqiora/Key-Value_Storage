#include <iostream>
#include <tuple>
#include "Model/BTree/BTree.h"
int main(){

  s21::BTree  temp(2);
  temp.UPLOAD("temp.txt");
  temp.SHOWALL();
  temp.SET("10", {"fsda", "fdsa", 22, "fdas", 21});
  temp.SET("12", {"fsda", "fdsa", 22, "fdas", 22});
  temp.SET("15", {"fsda", "fdsa", 22, "fdas", 23});
  temp.SET("20", {"fsda", "fdsa", 22, "fdas", 24});
  temp.SET("30", {"fsda", "fdsa", 22, "fdas", 25});
  temp.SET("90", {"fsda", "fdsa", 22, "fdas", 25});
  temp.SET("40", {"fsda", "fdsa", 22, "fdas", 26});
  temp.SET("55", {"fsda", "fdsa", 22, "fdas", 27});
  temp.SET("60", {"fsda", "fdsa", 22, "fdas", 27});
  temp.SET("25", {"fsda", "fdsa", 22, "fdas", 21});
  temp.SET("43", {"fsda", "fdsa", 22, "fdas", 21});
  temp.SET("89", {"fsda", "fdsa", 22, "fdas", 21});
  temp.EXPORT("temp.txt");
  std::cout<<"----------------------------------------------------\n";
  temp.SHOWALL();
  return 0;
}



#include <iostream>
#include "Model/BTree/BTree.h"

int main(){
  s21::Btree<int,double> tree(4);
  tree.SET(1,2.4);
  return 0;
}
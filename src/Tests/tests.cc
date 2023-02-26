#include <gtest/gtest.h>

#include "../Project/Model/BTree/BTree.h"
#include "../Project/Model/HashTable/HashTable.h"
#include "../Project/Model/SelfBalancingBinarySearchTree/SelfBalancingBinarySearchTree.h"

TEST(SelfBalancingSearchTree, Set) {
  s21::SelfBalancingBinarySearchTree tree;
  bool res =
      tree.Set({"123"}, {"Shvchenko", "Marina", 2000, "Novosibirsk", 100});
  EXPECT_TRUE(res);

  res = tree.Set({"123"}, {"Burov", "Oleg", 1999, "Novosibirsk", 34});
  EXPECT_FALSE(res);

  res = tree.Set({"12453"}, {"Kuhar", "Alexey", 1994, "Novosibirsk", 12});
  EXPECT_TRUE(res);

  res = tree.Set({"45"}, {"Kuhar", "Alexey", 1994, "Novosibirsk", 12});
  EXPECT_TRUE(res);
}

TEST(SelfBalancingSearchTree, Get) {
  s21::SelfBalancingBinarySearchTree tree;
  tree.Set({"123"}, {"Burov", "Oleg", 1999, "Novosibirsk", 34});

  std::optional<s21::DataS21Student> res = tree.Get("123");
  EXPECT_TRUE(res.has_value());

  res = tree.Get("lol");
  EXPECT_FALSE(res.has_value());

  tree.Set({"lol"}, {"Burov", "Oleg", 1999, "Novosibirsk", 34});
  res = tree.Get("lol");
  EXPECT_TRUE(res.has_value());
}

TEST(SelfBalancingSearchTree, Exists) {
  s21::SelfBalancingBinarySearchTree tree;
  tree.Set({"123"}, {"Shvchenko", "Marina", 2000, "Novosibirsk", 100});
  tree.Set({"123"}, {"Burov", "Oleg", 1999, "Novosibirsk", 34});
  tree.Set({"12453"}, {"Kuhar", "Alexey", 1994, "Novosibirsk", 12});
  tree.Set({"45"}, {"Kuhar", "Alexey", 1994, "Novosibirsk", 12});

  bool res = tree.Exists("123");
  EXPECT_TRUE(res);

  res = tree.Exists("lol");
  EXPECT_FALSE(res);

  res = tree.Exists("");
  EXPECT_FALSE(res);
}

TEST(SelfBalancingSearchTree, Del) {
  s21::SelfBalancingBinarySearchTree tree;
  tree.Set({"123"}, {"Shvchenko", "Marina", 2000, "Novosibirsk", 100});
  tree.Set({"123"}, {"Burov", "Oleg", 1999, "Novosibirsk", 34});
  tree.Set({"12453"}, {"Kuhar", "Alexey", 1994, "Novosibirsk", 12});
  tree.Set({"45"}, {"Kuhar", "Alexey", 1994, "Novosibirsk", 12});

  bool res = tree.Del("123");
  EXPECT_TRUE(res);
  EXPECT_FALSE(tree.Exists("123"));

  res = tree.Del("lol");
  EXPECT_FALSE(res);

  res = tree.Del("");
  EXPECT_FALSE(res);

  tree.Set({"BG"}, {"Wallace", "Christopher", 1972, "LosAngeles", 1});
  tree.Set({"ll"}, {"Cole", "Jermaine", 1985, "Frankfurt", 1000});
  tree.Set({"OFWGKTA"}, {"Okonma", "Tyler", 1991, "Hawthorne", 666});
  tree.Set({"SHOTED"}, {"Shakur", "Tupac", 1971, "NewYorkCity", 12});
  tree.Set({"Y"}, {"West", "Kanye", 1977, "Atlanta", 0});
  tree.Set({"GodsPlan"}, {"Graham", "Drake", 1986, "Toronto", 900});
  tree.Set({"Duckworth"}, {"Lamar", "Kendrick", 1987, "Compton", 6});
  tree.Set({"Future"}, {"Wilburn", "Nayvadius", 1983, "Atlanta", 0});
  tree.Set({"Offset"}, {"Cephus", "Kiari", 1991, "Lawrenceville", 88});

  for (auto& i : tree.Keys()) {
    tree.Del(i);
  }
  EXPECT_EQ(tree.Keys().size(), 0);
}

TEST(SelfBalancingSearchTree, Update) {
  s21::SelfBalancingBinarySearchTree tree;
  tree.Set({"123"}, {"Shvchenko", "Marina", 2000, "Novosibirsk", 100});
  tree.Set({"123"}, {"Burov", "Oleg", 1999, "Novosibirsk", 34});
  tree.Set({"12453"}, {"Kuhar", "Alexey", 1994, "Novosibirsk", 12});
  tree.Set({"45"}, {"Kuhar", "Alexey", 1994, "Novosibirsk", 12});

  bool res = tree.Update({"123"}, {"IZMENEN", "-", 99999999, "-", -1});
  EXPECT_EQ(tree.Get("123").value().GetLastname(), "IZMENEN");
  EXPECT_EQ(tree.Get("123").value().GetFirstname(), "Marina");
  EXPECT_EQ(tree.Get("123").value().GetYear(), 99999999);
  EXPECT_EQ(tree.Get("123").value().GetCity(), "Novosibirsk");
  EXPECT_EQ(tree.Get("123").value().GetCoins(), 100);
  EXPECT_TRUE(res);

  res = tree.Update({"kkkkk"}, {"kkkk", "kkk", 0, "-", -1});
  EXPECT_FALSE(res);
}

TEST(SelfBalancingSearchTree, Keys) {
  s21::SelfBalancingBinarySearchTree tree;
  std::vector<std::string> keys = tree.Keys();
  EXPECT_EQ(keys.size(), 0);

  tree.Set({"123"}, {"Shvchenko", "Marina", 2000, "Novosibirsk", 100});
  tree.Set({"123"}, {"Burov", "Oleg", 1999, "Novosibirsk", 34});
  tree.Set({"12453"}, {"Kuhar", "Alexey", 1994, "Novosibirsk", 12});
  tree.Set({"45"}, {"Kuhar", "Alexey", 1994, "Novosibirsk", 12});

  keys = tree.Keys();
  EXPECT_EQ(keys.size(), 3);
}

TEST(SelfBalancingSearchTree, Rename) {
  s21::SelfBalancingBinarySearchTree tree;
  tree.Set({"123"}, {"Shvchenko", "Marina", 2000, "Novosibirsk", 100});
  tree.Set({"123"}, {"Burov", "Oleg", 1999, "Novosibirsk", 34});
  tree.Set({"12453"}, {"Kuhar", "Alexey", 1994, "Novosibirsk", 12});
  tree.Set({"45"}, {"Kuhar", "Alexey", 1994, "Novosibirsk", 12});

  EXPECT_FALSE(tree.Exists("lol"));
  bool res = tree.Rename("123", "lol");
  EXPECT_TRUE(res);
  EXPECT_TRUE(tree.Exists("lol"));
}

TEST(SelfBalancingSearchTree, TTL) {
  s21::IDataOperations* tree = new s21::SelfBalancingBinarySearchTree;
  std::chrono::seconds sec(5);
  tree->Set({"lol"}, {"Cole", "Jermaine", 1985, "Frankfurt", 1000}, sec);
  std::thread th{[&tree]() {
    std::this_thread::sleep_for(std::chrono::seconds(3));
    auto tmp = tree->TTL("lol");
    EXPECT_TRUE(tmp >= 1 && tmp <= 3);
  }};
  th.join();
  delete tree;
}

TEST(SelfBalancingSearchTree, Find) {
  s21::SelfBalancingBinarySearchTree tree;
  tree.Set({"123"}, {"Shvchenko", "Marina", 2000, "Novosibirsk", 100});
  tree.Set({"123"}, {"Burov", "Oleg", 1999, "Novosibirsk", 34});
  tree.Set({"12453"}, {"Kuhar", "Alexey", 1994, "Novosibirsk", 12});
  tree.Set({"45"}, {"Kuhar", "Alexey", 1994, "Novosibirsk", 12});

  std::optional<std::vector<std::string>> res =
      tree.Find({"Kuhar", "Alexey", 1994, "Novosibirsk", 12});
  EXPECT_TRUE(res.has_value());
  EXPECT_EQ(res.value().size(), 2);

  res = tree.Find({"kva", "kva", 0000, "kva", 12});
  EXPECT_FALSE(res.has_value());
}

TEST(SelfBalancingSearchTree, ShowAll) {
  s21::SelfBalancingBinarySearchTree tree;

  std::vector<s21::DataS21Student> res = tree.ShowAll();
  EXPECT_EQ(res.size(), 0);

  tree.Set({"123"}, {"Shvchenko", "Marina", 2000, "Novosibirsk", 100});
  tree.Set({"123"}, {"Burov", "Oleg", 1999, "Novosibirsk", 34});
  tree.Set({"12453"}, {"Kuhar", "Alexey", 1994, "Novosibirsk", 12});
  tree.Set({"45"}, {"Kuhar", "Alexey", 1994, "Novosibirsk", 12});

  res = tree.ShowAll();
  EXPECT_EQ(res.size(), 3);
}

TEST(SelfBalancingSearchTree, Upload) {
  s21::SelfBalancingBinarySearchTree tree;
  int counter = tree.Upload("./Tests/Examples/1.txt");
  std::vector<s21::DataS21Student> res = tree.ShowAll();
  EXPECT_EQ(res.size(), counter);
}

TEST(SelfBalancingSearchTree, Export) {
  s21::SelfBalancingBinarySearchTree tree;
  tree.Set({"123"}, {"Shvchenko", "Marina", 2000, "Novosibirsk", 100});
  tree.Set({"123"}, {"Burov", "Oleg", 1999, "Novosibirsk", 34});
  tree.Set({"12453"}, {"Kuhar", "Alexey", 1994, "Novosibirsk", 12});
  tree.Set({"45"}, {"Kuhar", "Alexey", 1994, "Novosibirsk", 12});
  int counter = tree.Export("./Tests/Examples/out.txt");

  std::vector<s21::DataS21Student> res = tree.ShowAll();
  EXPECT_EQ(res.size(), counter);
}

TEST(Btree, Set) {
  s21::BTree tree;

  bool res =
      tree.Set({"BIG"}, {"Wallace", "Christopher", 1972, "Los Angeles", 1});
  EXPECT_TRUE(res);

  res = tree.Set({"BIG"}, {"Okonma", "Tyler", 1991, "Hawthorne", 666});
  EXPECT_FALSE(res);

  res = tree.Set({"lol"}, {"Cole", "Jermaine", 1985, "Frankfurt", 1000});
  EXPECT_TRUE(res);

  res = tree.Set({"SHOTTED"}, {"Shakur", "Tupac", 1971, "New York City", 12});
  EXPECT_TRUE(res);

  res = tree.Set({"Ye"}, {"West", "Kanye", 1977, "Atlanta", 0});
  EXPECT_TRUE(res);
}

TEST(Btree, Get) {
  s21::BTree tree(2);
  std::optional<s21::DataS21Student> res = tree.Get("1");
  EXPECT_FALSE(res.has_value());

  tree.Set({"1"}, {"Cole", "Jermaine", 1985, "Frankfurt", 1000});

  res = tree.Get("1");
  EXPECT_TRUE(res.has_value());

  res = tree.Get("SHOTTED");
  EXPECT_FALSE(res.has_value());

  tree.Set({"SHOTTED"}, {"Shakur", "Tupac", 1971, "New York City", 12});
  res = tree.Get("SHOTTED");
  EXPECT_TRUE(res.has_value());
}

TEST(Btree, Exists) {
  s21::BTree tree(2);
  tree.Set({"BIG"}, {"Wallace", "Christopher", 1972, "Los Angeles", 1});
  tree.Set({"lol"}, {"Cole", "Jermaine", 1985, "Frankfurt", 1000});
  tree.Set({"0"}, {"Okonma", "Tyler", 1991, "Hawthorne", 666});
  tree.Set({"SHOTTED"}, {"Shakur", "Tupac", 1971, "New York City", 12});
  tree.Set({"Ye"}, {"West", "Kanye", 1977, "Atlanta", 0});

  bool res = tree.Exists("BIG");
  EXPECT_TRUE(res);

  res = tree.Exists("olo");
  EXPECT_FALSE(res);

  res = tree.Exists("");
  EXPECT_FALSE(res);
}

TEST(Btree, Del) {
  s21::BTree tree(2);
  tree.Set({"BIG"}, {"Wallace", "Christopher", 1972, "Los Angeles", 1});
  tree.Set({"lol"}, {"Cole", "Jermaine", 1985, "Frankfurt", 1000});
  tree.Set({"0"}, {"Okonma", "Tyler", 1991, "Hawthorne", 666});
  tree.Set({"SHOTTED"}, {"Shakur", "Tupac", 1971, "New York City", 12});
  tree.Set({"Ye"}, {"West", "Kanye", 1977, "Atlanta", 0});

  bool res = tree.Del("BIG");

  EXPECT_TRUE(res);
  EXPECT_FALSE(tree.Exists("BIG"));

  res = tree.Del("olo");
  EXPECT_FALSE(res);

  res = tree.Del("");
  EXPECT_FALSE(res);

  tree.Set({"BG"}, {"Wallace", "Christopher", 1972, "LosAngeles", 1});
  tree.Set({"ll"}, {"Cole", "Jermaine", 1985, "Frankfurt", 1000});
  tree.Set({"OFWGKTA"}, {"Okonma", "Tyler", 1991, "Hawthorne", 666});
  tree.Set({"SHOTED"}, {"Shakur", "Tupac", 1971, "NewYorkCity", 12});
  tree.Set({"Y"}, {"West", "Kanye", 1977, "Atlanta", 0});
  tree.Set({"GodsPlan"}, {"Graham", "Drake", 1986, "Toronto", 900});
  tree.Set({"Duckworth"}, {"Lamar", "Kendrick", 1987, "Compton", 6});
  tree.Set({"Future"}, {"Wilburn", "Nayvadius", 1983, "Atlanta", 0});
  tree.Set({"Offset"}, {"Cephus", "Kiari", 1991, "Lawrenceville", 88});

  for (auto& i : tree.Keys()) {
    tree.Del(i);
  }
  EXPECT_EQ(tree.Keys().size(), 0);
}

TEST(Btree, Update) {
  s21::BTree tree(2);
  bool res_update = tree.Update({"kkkkk"}, {"kkkk", "kkk", 0, "-", -1});
  EXPECT_FALSE(res_update);

  tree.Set({"BIG"}, {"Wallace", "Christopher", 1972, "Los Angeles", 1});

  res_update = tree.Update({"BIG"}, {"IZMENEN", "-", 99999999, "-", -1});
  EXPECT_EQ(tree.Get("BIG").value().GetLastname(), "IZMENEN");
  EXPECT_EQ(tree.Get("BIG").value().GetFirstname(), "Christopher");
  EXPECT_EQ(tree.Get("BIG").value().GetYear(), 99999999);
  EXPECT_EQ(tree.Get("BIG").value().GetCity(), "Los Angeles");
  EXPECT_EQ(tree.Get("BIG").value().GetCoins(), 1);
  EXPECT_TRUE(res_update);

  res_update = tree.Update({"kkkkk"}, {"kkkk", "kkk", 0, "-", -1});
  EXPECT_FALSE(res_update);
}

TEST(Btree, Keys) {
  s21::BTree tree(2);
  std::vector<std::string> keys = tree.Keys();
  EXPECT_EQ(keys.size(), 0);

  tree.Set({"BIG"}, {"Wallace", "Christopher", 1972, "Los Angeles", 1});
  tree.Set({"lol"}, {"Cole", "Jermaine", 1985, "Frankfurt", 1000});
  tree.Set({"0"}, {"Okonma", "Tyler", 1991, "Hawthorne", 666});

  auto keys_v = tree.Keys();
  EXPECT_EQ(keys_v.size(), 3);
}

TEST(Btree, Rename) {
  s21::IDataOperations* tree = new s21::BTree(2);
  tree->Set({"BIG"}, {"Wallace", "Christopher", 1972, "Los Angeles", 1});
  tree->Set({"lol"}, {"Cole", "Jermaine", 1985, "Frankfurt", 1000});
  tree->Set({"0"}, {"Okonma", "Tyler", 1991, "Hawthorne", 666});
  tree->Set({"SHOTTED"}, {"Shakur", "Tupac", 1971, "New York City", 12});
  tree->Set({"Ye"}, {"West", "Kanye", 1977, "Atlanta", 0});

  EXPECT_FALSE(tree->Exists("olo"));
  bool res = tree->Rename("lol", "olo");
  EXPECT_TRUE(res);
  EXPECT_TRUE(tree->Exists("olo"));
}

TEST(Btree, TTL) {
  s21::IDataOperations* tree = new s21::BTree(2);
  std::chrono::seconds sec(5);
  tree->Set({"lol"}, {"Cole", "Jermaine", 1985, "Frankfurt", 1000}, sec);
  std::thread th{[&tree]() {
    std::this_thread::sleep_for(std::chrono::seconds(3));
    auto tmp = tree->TTL("lol");
    EXPECT_TRUE(tmp >= 1 && tmp <= 3);
  }};
  th.join();
  delete tree;
}

TEST(Btree, Find) {
  s21::BTree tree(2);
  tree.Set({"BIG"}, {"Wallace", "Christopher", 1972, "Los Angeles", 1});
  tree.Set({"lol"}, {"Cole", "Jermaine", 1985, "Frankfurt", 1000});
  tree.Set({"0"}, {"Okonma", "Tyler", 1991, "Hawthorne", 666});
  tree.Set({"SHOTTED"}, {"Shakur", "Tupac", 1971, "New York City", 12});
  tree.Set({"Ye"}, {"West", "Kanye", 1977, "Atlanta", 0});

  auto res = tree.Find({"Shakur", "Tupac", 1971, "New York City", 12});
  EXPECT_TRUE(res.has_value());
  EXPECT_EQ(res.value().size(), 1);

  res = tree.Find({"kva", "kva", 0000, "kva", 12});
  EXPECT_EQ(res.value().size(), 0);
}

TEST(Btree, ShowAll) {
  s21::BTree tree(2);
  std::vector<s21::DataS21Student> res = tree.ShowAll();
  EXPECT_EQ(res.size(), 0);

  tree.Set({"BIG"}, {"Wallace", "Christopher", 1972, "Los Angeles", 1});
  tree.Set({"lol"}, {"Cole", "Jermaine", 1985, "Frankfurt", 1000});
  tree.Set({"0"}, {"Okonma", "Tyler", 1991, "Hawthorne", 666});
  tree.Set({"SHOTTED"}, {"Shakur", "Tupac", 1971, "New York City", 12});
  tree.Set({"Ye"}, {"West", "Kanye", 1977, "Atlanta", 0});
  res = tree.ShowAll();
  EXPECT_EQ(res.size(), 5);
}

TEST(Btree, Upload) {
  s21::BTree tree(2);
  int counter = tree.Upload("./Tests/Examples/1.txt");
  std::vector<s21::DataS21Student> res = tree.ShowAll();
  EXPECT_EQ(res.size(), counter);
}

TEST(Btree, Export) {
  s21::BTree tree(2);
  tree.Set({"BIG"}, {"Wallace", "Christopher", 1972, "Los Angeles", 1});
  tree.Set({"lol"}, {"Cole", "Jermaine", 1985, "Frankfurt", 1000});
  tree.Set({"0"}, {"Okonma", "Tyler", 1991, "Hawthorne", 666});
  tree.Set({"SHOTTED"}, {"Shakur", "Tupac", 1971, "New York City", 12});
  tree.Set({"Ye"}, {"West", "Kanye", 1977, "Atlanta", 0});
  int counter = tree.Export("./Tests/Examples/out.txt");

  std::vector<s21::DataS21Student> res = tree.ShowAll();
  EXPECT_EQ(res.size(), counter);
}

TEST(HashTable, Set) {
  s21::HashTable tree;
  bool res =
      tree.Set({"123"}, {"Shvchenko", "Marina", 2000, "Novosibirsk", 100});
  EXPECT_TRUE(res);

  res = tree.Set({"123"}, {"Burov", "Oleg", 1999, "Novosibirsk", 34});
  EXPECT_FALSE(res);

  res = tree.Set({"12453"}, {"Kuhar", "Alexey", 1994, "Novosibirsk", 12});
  EXPECT_TRUE(res);

  res = tree.Set({"45"}, {"Kuhar", "Alexey", 1994, "Novosibirsk", 12});
  EXPECT_TRUE(res);
}

TEST(HashTable, Get) {
  s21::HashTable tree;
  tree.Set({"123"}, {"Burov", "Oleg", 1999, "Novosibirsk", 34});

  std::optional<s21::DataS21Student> res = tree.Get("123");
  EXPECT_TRUE(res.has_value());

  res = tree.Get("lol");
  EXPECT_FALSE(res.has_value());

  tree.Set({"lol"}, {"Burov", "Oleg", 1999, "Novosibirsk", 34});
  res = tree.Get("lol");
  EXPECT_TRUE(res.has_value());
}

TEST(HashTable, Exists) {
  s21::HashTable tree;
  tree.Set({"123"}, {"Shvchenko", "Marina", 2000, "Novosibirsk", 100});
  tree.Set({"123"}, {"Burov", "Oleg", 1999, "Novosibirsk", 34});
  tree.Set({"12453"}, {"Kuhar", "Alexey", 1994, "Novosibirsk", 12});
  tree.Set({"45"}, {"Kuhar", "Alexey", 1994, "Novosibirsk", 12});

  bool res = tree.Exists("123");
  EXPECT_TRUE(res);

  res = tree.Exists("lol");
  EXPECT_FALSE(res);

  res = tree.Exists("");
  EXPECT_FALSE(res);
}

TEST(HashTable, Del) {
  s21::HashTable tree;
  tree.Set({"123"}, {"Shvchenko", "Marina", 2000, "Novosibirsk", 100});
  tree.Set({"1234"}, {"Burov", "Oleg", 1999, "Novosibirsk", 34});
  tree.Set({"12453"}, {"Kuhar", "Alexey", 1994, "Novosibirsk", 12});
  tree.Set({"45"}, {"Kuhar", "Alexey", 1994, "Novosibirsk", 12});

  bool res = tree.Del("123");

  EXPECT_TRUE(res);
  EXPECT_FALSE(tree.Exists("123"));

  res = tree.Del("lol");
  EXPECT_FALSE(res);

  res = tree.Del("");
  EXPECT_FALSE(res);

  tree.Set({"BG"}, {"Wallace", "Christopher", 1972, "LosAngeles", 1});
  tree.Set({"ll"}, {"Cole", "Jermaine", 1985, "Frankfurt", 1000});
  tree.Set({"OFWGKTA"}, {"Okonma", "Tyler", 1991, "Hawthorne", 666});
  tree.Set({"SHOTED"}, {"Shakur", "Tupac", 1971, "NewYorkCity", 12});
  tree.Set({"Y"}, {"West", "Kanye", 1977, "Atlanta", 0});
  tree.Set({"GodsPlan"}, {"Graham", "Drake", 1986, "Toronto", 900});
  tree.Set({"Duckworth"}, {"Lamar", "Kendrick", 1987, "Compton", 6});
  tree.Set({"Future"}, {"Wilburn", "Nayvadius", 1983, "Atlanta", 0});
  tree.Set({"Offset"}, {"Cephus", "Kiari", 1991, "Lawrenceville", 88});

  for (auto& i : tree.Keys()) {
    tree.Del(i);
  }
  EXPECT_EQ(tree.Keys().size(), 0);
}

TEST(HashTable, Update) {
  s21::HashTable tree;
  tree.Set({"123"}, {"Shvchenko", "Marina", 2000, "Novosibirsk", 100});
  tree.Set({"1234"}, {"Burov", "Oleg", 1999, "Novosibirsk", 34});
  tree.Set({"12453"}, {"Kuhar", "Alexey", 1994, "Novosibirsk", 12});
  tree.Set({"45"}, {"Kuhar", "Alexey", 1994, "Novosibirsk", 12});

  bool res = tree.Update({"123"}, {"IZMENEN", "-", 99999999, "-", -1});
  EXPECT_EQ(tree.Get("123").value().GetLastname(), "IZMENEN");
  EXPECT_EQ(tree.Get("123").value().GetFirstname(), "Marina");
  EXPECT_EQ(tree.Get("123").value().GetYear(), 99999999);
  EXPECT_EQ(tree.Get("123").value().GetCity(), "Novosibirsk");
  EXPECT_EQ(tree.Get("123").value().GetCoins(), 100);
  EXPECT_TRUE(res);

  res = tree.Update({"kkkkk"}, {"kkkk", "kkk", 0, "-", -1});
  EXPECT_FALSE(res);
}

TEST(HashTable, Keys) {
  s21::HashTable tree;
  std::vector<std::string> keys = tree.Keys();
  EXPECT_EQ(keys.size(), 0);

  tree.Set({"123"}, {"Shvchenko", "Marina", 2000, "Novosibirsk", 100});
  tree.Set({"1234"}, {"Burov", "Oleg", 1999, "Novosibirsk", 34});
  tree.Set({"12453"}, {"Kuhar", "Alexey", 1994, "Novosibirsk", 12});
  tree.Set({"45"}, {"Kuhar", "Alexey", 1994, "Novosibirsk", 12});

  keys = tree.Keys();
  EXPECT_EQ(keys.size(), 4);
}

TEST(HashTable, Rename) {
  s21::HashTable tree;
  tree.Set({"123"}, {"Shvchenko", "Marina", 2000, "Novosibirsk", 100});
  tree.Set({"123"}, {"Burov", "Oleg", 1999, "Novosibirsk", 34});
  tree.Set({"12453"}, {"Kuhar", "Alexey", 1994, "Novosibirsk", 12});
  tree.Set({"45"}, {"Kuhar", "Alexey", 1994, "Novosibirsk", 12});

  EXPECT_FALSE(tree.Exists("lol"));
  bool res = tree.Rename("123", "lol");
  EXPECT_TRUE(res);
  EXPECT_TRUE(tree.Exists("lol"));
  EXPECT_FALSE(tree.Exists("123"));
}

TEST(HashTable, Find) {
  s21::HashTable tree;
  tree.Set({"123"}, {"Shvchenko", "Marina", 2000, "Novosibirsk", 100});
  tree.Set({"123"}, {"Burov", "Oleg", 1999, "Novosibirsk", 34});
  tree.Set({"12453"}, {"Kuhar", "Alexey", 1994, "Novosibirsk", 12});
  tree.Set({"45"}, {"Kuhar", "Alexey", 1994, "Novosibirsk", 12});

  std::optional<std::vector<std::string>> res =
      tree.Find({"Kuhar", "Alexey", 1994, "Novosibirsk", 12});
  EXPECT_TRUE(res.has_value());
  EXPECT_EQ(res.value().size(), 2);

  res = tree.Find({"kva", "kva", 0000, "kva", 12});
  EXPECT_FALSE(res.has_value());
}

TEST(HashTable, ShowAll) {
  s21::HashTable tree;

  std::vector<s21::DataS21Student> res = tree.ShowAll();
  EXPECT_EQ(res.size(), 0);

  tree.Set({"123"}, {"Shvchenko", "Marina", 2000, "Novosibirsk", 100});
  tree.Set({"123"}, {"Burov", "Oleg", 1999, "Novosibirsk", 34});
  tree.Set({"12453"}, {"Kuhar", "Alexey", 1994, "Novosibirsk", 12});
  tree.Set({"45"}, {"Kuhar", "Alexey", 1994, "Novosibirsk", 12});

  res = tree.ShowAll();
  EXPECT_EQ(res.size(), 3);
}

TEST(HashTable, Upload) {
  s21::HashTable tree;
  int counter = tree.Upload("./Tests/Examples/1.txt");
  std::vector<s21::DataS21Student> res = tree.ShowAll();
  EXPECT_EQ(res.size(), counter);
}

TEST(HashTable, Export) {
  s21::HashTable tree;
  tree.Set({"123"}, {"Shvchenko", "Marina", 2000, "Novosibirsk", 100});
  tree.Set({"123"}, {"Burov", "Oleg", 1999, "Novosibirsk", 34});
  tree.Set({"12453"}, {"Kuhar", "Alexey", 1994, "Novosibirsk", 12});
  tree.Set({"45"}, {"Kuhar", "Alexey", 1994, "Novosibirsk", 12});
  int counter = tree.Export("./Tests/Examples/out.txt");

  std::vector<s21::DataS21Student> res = tree.ShowAll();
  EXPECT_EQ(res.size(), counter);
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

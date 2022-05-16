// This file and its comments were written and given to me by reddit user
// u/-D_GLIBCXX_DEBUG

#include <algorithm>
#include <iostream>

#include "RedBlackTree.hpp"  // 3d5b1444cdc2525721f21da7a2863f56756936a8

// test1() reveals 4 bugs
// reminder: range-based for-loop calls begin() and end()
// and then uses operator!=(), operator*() and operator++() on the iterator
// (though in the empty case it won't call the last two).
// note: this test also calls the destructor when the tree is empty.
static void test1() {
  RedBlackTree<int, char> tree1;
  for (auto &&x : tree1) {
  }
}
// test2() reveals 2 bugs
static void test2() {
  RedBlackTree<int, char> tree1;
  tree1[0] = 'a';
  assert(tree1.size() == 1);
  auto tree2 = tree1;  // copy-ctor
  assert(tree2.size() == 1);
}
static void test3() {
  RedBlackTree<int, char> tree1;
  tree1[0] = 'a';
  assert(tree1.size() == 1);
  auto tree2 = std::move(tree1);  // move-ctor
  assert(tree1.size() == 0);      // assumes move swaps the tree's root and size
  assert(tree2.size() == 1);
}
static void test4() {
  RedBlackTree<int, char> tree1, tree2;
  tree1[0] = 'a';
  assert(tree1.size() == 1);
  assert(tree2.size() == 0);
  tree2 = tree1;  // copy-assign
  assert(tree1.size() == 1);
  assert(tree2.size() == 1);
}
static void test5() {
  RedBlackTree<int, char> tree1, tree2;
  tree1[0] = 'a';
  assert(tree1.size() == 1);
  assert(tree2.size() == 0);
  tree2 = std::move(tree1);   // move-assign
  assert(tree1.size() == 0);  // assumes move swaps the tree's root and size
  assert(tree2.size() == 1);
}
static void test6() {
  RedBlackTree<int, char> tree1;
  tree1[0] = 'a';
  assert(tree1.size() == 1);
  assert(tree1.begin() != tree1.end());
  tree1 = tree1;              // self copy-assign
  assert(tree1.size() == 1);  // assumes self copy-assign is a nop
  assert(tree1.begin() != tree1.end());
}
static void test7() {
  RedBlackTree<int, char> tree1;
  tree1[0] = 'a';
  assert(tree1.size() == 1);
  assert(tree1.begin() != tree1.end());
  tree1 = std::move(tree1);   // self move-assign
  assert(tree1.size() == 1);  // assumes self move-assign is a nop
  assert(tree1.begin() != tree1.end());
}

int main() {
  test1();
  printf("test1 passed\n");
  test2();
  printf("test2 passed\n");
  test3();
  printf("test3 passed\n");
  test4();
  printf("test4 passed\n");
  test5();
  printf("test5 passed\n");
  test6();
  printf("test6 passed\n");
  test7();
  printf("test7 passed\n");

  return 0;
}
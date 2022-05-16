// This file and its comments are based on a file written and given to me by
// reddit user u/-D_GLIBCXX_DEBUG for my RedBlackTree version

#include <algorithm>
#include <cassert>
#include <iostream>

#include "BinarySearchTreeSmart.hpp"

static void test2() {
  BinarySearchTreeSmart tree1;
  tree1.insert(12);
  assert(tree1.size() == 1);
  auto tree2 = tree1;  // copy-ctor
  assert(tree2.size() == 1);
}
static void test3() {
  BinarySearchTreeSmart tree1;
  tree1.insert(12);
  assert(tree1.size() == 1);
  auto tree2 = std::move(tree1);  // move-ctor
  assert(tree1.size() == 0);      // assumes move swaps the tree's root and size
  assert(tree2.size() == 1);
}
static void test4() {
  BinarySearchTreeSmart tree1, tree2;
  tree1.insert(12);
  assert(tree1.size() == 1);
  assert(tree2.size() == 0);
  tree2 = tree1;  // copy-assign
  assert(tree1.size() == 1);
  assert(tree2.size() == 1);
}
static void test5() {
  BinarySearchTreeSmart tree1, tree2;
  tree1.insert(12);
  assert(tree1.size() == 1);
  assert(tree2.size() == 0);
  tree2 = std::move(tree1);   // move-assign
  assert(tree1.size() == 0);  // assumes move swaps the tree's root and size
  assert(tree2.size() == 1);
}
static void test6() {
  BinarySearchTreeSmart tree1;
  tree1.insert(12);
  assert(tree1.size() == 1);
  tree1 = tree1;              // self copy-assign
  assert(tree1.size() == 1);  // assumes self copy-assign is a nop}
}
static void test7() {
  BinarySearchTreeSmart tree1;
  tree1.insert(12);
  assert(tree1.size() == 1);
  tree1 = std::move(tree1);   // self move-assign
  assert(tree1.size() == 1);  // assumes self move-assign is a nop}
}

int main() {
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
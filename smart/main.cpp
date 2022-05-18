// Smart version
#include <cstdlib>
#include <iomanip>
#include <iostream>

#include "BinarySearchTreeSmart.hpp"

int main() {
  std::cout << std::boolalpha;
  BinarySearchTreeSmart tree;
  std::cout << "tree.empty() = " << tree.empty() << std::endl;

  tree.insert(9);
  tree.insert(4);
  tree.insert(6);
  tree.insert(20);
  tree.insert(170);
  tree.insert(15);
  tree.insert(1);
  std::cout << "tree.empty() = " << tree.empty() << std::endl;

  std::cout << "9 is found in tree = " << tree.contains(9) << std::endl;
  std::cout << "4 is found in tree = " << tree.contains(4) << std::endl;
  std::cout << "6 is found in tree = " << tree.contains(6) << std::endl;
  std::cout << "20 is found in tree = " << tree.contains(20) << std::endl;
  std::cout << "170 is found in tree = " << tree.contains(170) << std::endl;
  std::cout << "15 is found in tree = " << tree.contains(15) << std::endl;
  std::cout << "30 is found in tree = " << tree.contains(30) << std::endl;

  int MAX = 1000;
  srand(time(0));
  BinarySearchTreeSmart tree0;
  for (int i{}; i < 100; ++i) {
    tree0.insert(rand() % MAX + 1);
  }

  std::cout << "\nTraversing tree0 inOrder = \n";
  tree0.displayTree(Order::inOrder);
  std::cout << "\nTraversing tree0 preOrder = \n";
  tree0.displayTree(Order::preOrder);
  std::cout << "\nTraversing tree0 postOrder = \n";
  tree0.displayTree(Order::postOrder);
  std::cout << "\nTraversing tree0 elementsOnly = ";
  tree0.displayTree(Order::elementsOnly);

  BinarySearchTreeSmart tree1;
  // Move assignment operator
  tree1 = std::move(tree0);
  // Copy constructor
  BinarySearchTreeSmart tree2(tree1);
  // Copy assignment operator
  BinarySearchTreeSmart tree3 = tree2;

  std::cout << "\n\nTraversing tree1 which was move assigned from tree0 "
               "(elementsOnly) = ";
  tree1.displayTree(Order::elementsOnly);
  std::cout << "\n\nTraversing tree2 which was copy constructed from tree1 "
               "(elementsOnly) = ";
  tree2.displayTree(Order::elementsOnly);
  std::cout << "\n\nTraversing tree3 which was copy assigned from tree2 "
               "(elementsOnly) = ";
  tree3.displayTree(Order::elementsOnly);
  std::cout << "\n\nTraversing tree0 again after it was move assigned to tree1 "
               "(elementsOnly) = ";
  tree0.displayTree(Order::elementsOnly);
  // Move constructor
  BinarySearchTreeSmart tree4(std::move(tree3));
  std::cout << "\nTraversing tree4 which was move constructed from tree3 "
               "(elementsOnly) = ";
  tree4.displayTree(Order::elementsOnly);
  std::cout << "\n\nTraversing tree3 again after it was move constructed to "
               "tree4 (elementsOnly) = ";
  tree3.displayTree(Order::elementsOnly);
  std::cout << "\nPerforming tree4.clear()..." << std::endl;
  tree4.clear();
  std::cout << "tree4.empty() = " << tree4.empty() << std::endl;
  std::cout << "Traversing tree4 which was just emptied "
               "(elementsOnly) = ";
  tree4.displayTree(Order::elementsOnly);

  puts("\n");

  return 0;
}
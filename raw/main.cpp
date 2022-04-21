//Raw version
#include <iostream>
#include <iomanip>
#include "BinarySearchTree.hpp"
#include <cstdlib>

int main() {
  BinarySearchTree tree;  

  std::cout << std::boolalpha;
  std::cout << "\ntree.empty() = " << tree.empty() << std::endl;
  std::cout << "Size of tree = " << tree.size() << std::endl;
  std::cout << "Inserting 7 elements..." << std::endl;
   
  tree.insert(9);
  tree.insert(4);
  tree.insert(6);
  tree.insert(20);
  tree.insert(170);
  tree.insert(15);
  tree.insert(1);

  std::cout << "tree.empty() = " << tree.empty() << std::endl;
  std::cout << "Size of tree = " << tree.size() << std::endl;
  std::cout << "\nDisplaying tree elements: ";
  tree.displayTree("elementsOnly");

  std::cout << "\n\n9 is found in tree = " << tree.contains(9) << std::endl;
  std::cout << "4 is found in tree = " << tree.contains(4) << std::endl;
  std::cout << "6 is found in tree = " << tree.contains(6) << std::endl;
  std::cout << "20 is found in tree = " << tree.contains(20) << std::endl;
  std::cout << "170 is found in tree = " << tree.contains(170) << std::endl;
  std::cout << "15 is found in tree = " << tree.contains(15) << std::endl;       
  std::cout << "30 is found in tree = " << tree.contains(30) << std::endl;
  std::cout << "1 is found in tree = " << tree.contains(1) << std::endl;

  tree.erase(4);
  std::cout << "\nDisplaying tree elements after removing 4: ";
  tree.displayTree("elementsOnly");
  std::cout << "\nSize of tree = " << tree.size() << std::endl;
  std::cout << "\n\n9 is found in tree = " << tree.contains(9) << std::endl;
  std::cout << "4 is found in tree = " << tree.contains(4) << std::endl;
  std::cout << "6 is found in tree = " << tree.contains(6) << std::endl;
  std::cout << "20 is found in tree = " << tree.contains(20) << std::endl;
  std::cout << "170 is found in tree = " << tree.contains(170) << std::endl;
  std::cout << "15 is found in tree = " << tree.contains(15) << std::endl;       
  std::cout << "30 is found in tree = " << tree.contains(30) << std::endl;
  std::cout << "1 is found in tree = " << tree.contains(1) << std::endl;

  tree.erase(9);
  std::cout << "\nDisplaying tree elements after removing 9 (the head): ";
  tree.displayTree("elementsOnly");
  std::cout << "\nSize of tree = " << tree.size() << std::endl;
  std::cout << "\n\n9 is found in tree = " << tree.contains(9) << std::endl;
  std::cout << "4 is found in tree = " << tree.contains(4) << std::endl;
  std::cout << "6 is found in tree = " << tree.contains(6) << std::endl;
  std::cout << "20 is found in tree = " << tree.contains(20) << std::endl;
  std::cout << "170 is found in tree = " << tree.contains(170) << std::endl;
  std::cout << "15 is found in tree = " << tree.contains(15) << std::endl;       
  std::cout << "30 is found in tree = " << tree.contains(30) << std::endl;
  std::cout << "1 is found in tree = " << tree.contains(1) << std::endl;

  tree.erase(20);
  std::cout << "\nDisplaying tree elements after removing 20: ";
  tree.displayTree("elementsOnly");
  std::cout << "\nSize of tree = " << tree.size() << std::endl;
  std::cout << "\n\n9 is found in tree = " << tree.contains(9) << std::endl;
  std::cout << "4 is found in tree = " << tree.contains(4) << std::endl;
  std::cout << "6 is found in tree = " << tree.contains(6) << std::endl;
  std::cout << "20 is found in tree = " << tree.contains(20) << std::endl;
  std::cout << "170 is found in tree = " << tree.contains(170) << std::endl;
  std::cout << "15 is found in tree = " << tree.contains(15) << std::endl;       
  std::cout << "30 is found in tree = " << tree.contains(30) << std::endl;
  std::cout << "1 is found in tree = " << tree.contains(1) << std::endl;

  tree.clear();
  std::cout << "\nSize of tree after tree.clear()= " << tree.size() << std::endl;
  
  int MAX = 1000;
  int QTY = 20;
  srand(time(0));
  std::cout << "Creating tree0 and inserting " << QTY << " elements between 1 and " << MAX << std::endl;
  BinarySearchTree tree0;
  for(int i {}; i < QTY; ++i) {
    tree0.insert(rand()%MAX + 1);
  }

  std::cout << "\nTraversing tree0 inOrder = \n";
  tree0.displayTree("inOrder");
  std::cout << "\nTraversing tree0 preOrder = \n";
  tree0.displayTree("preOrder");
  std::cout << "\nTraversing tree0 postOrder = \n";
  tree0.displayTree("postOrder");
  std::cout << "\nTraversing tree0 elementsOnly = ";
  tree0.displayTree("elementsOnly");

  
  BinarySearchTree tree1;
  //Move assignment operator
  tree1 = std::move(tree0);
  //Copy constructor
  BinarySearchTree tree2(tree1);
  //Copy assignment operator
  BinarySearchTree tree3 = tree2;
  
  std::cout << "\n\nTraversing tree1 which was move assigned from tree0 (elementsOnly) = ";
  tree1.displayTree("elementsOnly");
  std::cout << "\n\nTraversing tree2 which was copy constructed from tree1 (elementsOnly) = ";
  tree2.displayTree("elementsOnly");
  std::cout << "\n\nTraversing tree3 which was copy assigned from tree2 (elementsOnly) = ";
  tree3.displayTree("elementsOnly");
  std::cout << "\n\nTraversing tree0 again after it was move assigned to tree1 (elementsOnly) = ";
  tree0.displayTree("elementsOnly");
  //Move constructor
  BinarySearchTree tree4(std::move(tree3));
  std::cout << "\n\nTraversing tree4 which was move constructed from tree3 (elementsOnly) = ";
  tree4.displayTree("elementsOnly");
  std::cout << "\n\nTraversing tree3 again after it was move constructed to tree4 (elementsOnly) = ";
  tree3.displayTree("elementsOnly");
  
  puts("\n");
 
  return 0;
}
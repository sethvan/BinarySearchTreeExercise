#include <iostream>
#include <vector>
#include "VecTree.hpp"
#include <iomanip>


int main(){
  VecTree<int> tree {};
  
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

  std::cout << "\nTraversing tree preOrder = \n";
  tree.displayTree("preOrder");

  tree.erase(9);
  std::cout << "You are here5" << std::endl;
  std::cout << "\nDisplaying tree elements after removing 9 (the head): ";
  std::cout << "You are here6" << std::endl;
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


  std::cout << "\nTraversing tree inOrder = \n";
  tree.displayTree("inOrder");
  std::cout << "\nTraversing tree preOrder = \n";
  tree.displayTree("preOrder");
  std::cout << "\nTraversing tree postOrder = \n";
  tree.displayTree("postOrder");
  std::cout << "\nTraversing tree elementsOnly = ";
  tree.displayTree("elementsOnly");

  return 0;

}
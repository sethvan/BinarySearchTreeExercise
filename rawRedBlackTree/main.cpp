#include <iostream>
#include "RedBlackTree.hpp"

int main(){
  RedBlackTree<int,char> tree;

  for(int i = 0; i < 26; ++i)    
    tree.insert(i, static_cast<char>(i + 97));
  puts("");

  tree.displayTree(RedBlackTree<int, char>::Order::preOrder);
  puts("");
  tree.displayTree(RedBlackTree<int, char>::Order::elementsOnly);
  std::cout << "\n\nHeight = " << tree.height() << std::endl;
  std::cout << "Black nodes = " << tree.blackNodes() << std::endl;
  puts("\n");
  tree.erase(11);
  std::cout << "erasing 11...\n" << std::endl;
  tree.displayTree(RedBlackTree<int, char>::Order::preOrder);
  puts("");
  tree.displayTree(RedBlackTree<int, char>::Order::elementsOnly);
  std::cout << "\n\nHeight = " << tree.height() << std::endl;
  std::cout << "Black nodes = " << tree.blackNodes() << std::endl;
  puts("\n");
  tree.erase(19);
  std::cout << "erasing 19...\n" << std::endl;
  tree.displayTree(RedBlackTree<int, char>::Order::preOrder);
  puts("");
  tree.displayTree(RedBlackTree<int, char>::Order::elementsOnly);
  std::cout << "\n\nHeight = " << tree.height() << std::endl;
  std::cout << "Black nodes = " << tree.blackNodes() << std::endl;
  puts("\n");
  tree.erase(4);
  std::cout << "erasing 4...\n" << std::endl;
  tree.displayTree(RedBlackTree<int, char>::Order::preOrder);
  puts("");
  tree.displayTree(RedBlackTree<int, char>::Order::elementsOnly);
  std::cout << "\n\nHeight = " << tree.height() << std::endl;
  std::cout << "Black nodes = " << tree.blackNodes() << std::endl;
  puts("\n");
  tree.erase(22);
  std::cout << "erasing 22...\n" << std::endl;
  tree.displayTree(RedBlackTree<int, char>::Order::preOrder);
  puts("");
  tree.displayTree(RedBlackTree<int, char>::Order::elementsOnly);
  std::cout << "\n\nHeight = " << tree.height() << std::endl;
  std::cout << "Black nodes = " << tree.blackNodes() << std::endl;

  std::cout << "tree[3] = " << tree[3] << std::endl;
  std::cout << "Changing tree[3] to '!'" << std::endl;
  tree[3] = '!';
  std::cout << "tree[3] = " << tree[3] << std::endl;
  std::cout << "setting tree[300] to '#'" << std::endl;
  tree[300] = '#';
  std::cout << "tree[300] = " << tree[300] << std::endl;
  puts("\n");
  
  tree.displayTree(RedBlackTree<int, char>::Order::elementsOnly);

  return 0;
}
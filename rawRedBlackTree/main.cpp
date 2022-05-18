#include <algorithm>
#include <iostream>

#include "RedBlackTree.hpp"

int main() {
  RedBlackTree<int, char> tree1;
  tree1.insert(0, 'a');
  tree1.erase(0);
  tree1.insert(0, 'a');
  tree1.insert(1, 'b');
  tree1.insert(2, 'c');

  RedBlackTree<int, char> tree;

  for (int i = 0; i < 26; ++i) tree[i] = static_cast<char>(i + 97);
  puts("");

  auto it = tree.begin();
  while (it != tree.end()) {
    std::cout << "key = " << it->first << ", value = " << it->second
              << std::endl;
    ++it;
  }
  puts("");
  it = tree.begin();
  std::cout << "it->second = " << (*it).second << std::endl;
  (*it).second = '$';

  auto itEnd = tree.end();
  --itEnd;
  std::cout << "tree.end() - 1 -> first = " << itEnd->first << "\n"
            << std::endl;

  for (const auto pair : tree) {
    std::cout << "key = " << pair.first << ", value = " << pair.second
              << std::endl;
  }
  puts("");

  auto it3 = tree.begin();

  std::cout << "tree.begin().first = " << it3->first << std::endl;
  // it3->first = 35;
  std::cout << "tree.begin().first = " << it3->first << std::endl;

  tree.displayTree(Order::preOrder);
  puts("");

  int num = std::count_if(
      tree.begin(), tree.end(),
      [](std::pair<int, char> pair) { return pair.second % 3 == 0; });
  std::cout << "Num = " << num << std::endl;

  puts("");
  auto it20 = tree.find(20);
  std::cout << "it20->second = " << it20->second << std::endl;

  // tree.displayTree(Order::elementsOnly);
  // std::cout << "\n\nHeight = " << tree.height() << std::endl;
  // std::cout << "Black nodes = " << tree.blackNodes() << std::endl;
  // puts("\n");
  // tree.erase(11);
  // std::cout << "erasing 11...\n" << std::endl;
  // tree.displayTree(Order::preOrder);
  // puts("");
  // tree.displayTree(Order::elementsOnly);
  // std::cout << "\n\nHeight = " << tree.height() << std::endl;
  // std::cout << "Black nodes = " << tree.blackNodes() << std::endl;
  // puts("\n");
  // tree.erase(19);
  // std::cout << "erasing 19...\n" << std::endl;
  // tree.displayTree(Order::preOrder);
  // puts("");
  // tree.displayTree(Order::elementsOnly);
  // std::cout << "\n\nHeight = " << tree.height() << std::endl;
  // std::cout << "Black nodes = " << tree.blackNodes() << std::endl;
  // puts("\n");
  // tree.erase(4);
  // std::cout << "erasing 4...\n" << std::endl;
  // tree.displayTree(Order::preOrder);
  // puts("");
  // tree.displayTree(Order::elementsOnly);
  // std::cout << "\n\nHeight = " << tree.height() << std::endl;
  // std::cout << "Black nodes = " << tree.blackNodes() << std::endl;
  // puts("\n");
  // tree.erase(22);
  // std::cout << "erasing 22...\n" << std::endl;
  // tree.displayTree(Order::preOrder);
  // puts("");
  // tree.displayTree(Order::elementsOnly);
  // std::cout << "\n\nHeight = " << tree.height() << std::endl;
  // std::cout << "Black nodes = " << tree.blackNodes() << std::endl;

  // std::cout << "tree[3] = " << tree[3] << std::endl;
  // std::cout << "Changing tree[3] to '!'" << std::endl;
  // tree[3] = '!';
  // std::cout << "tree[3] = " << tree[3] << std::endl;
  // std::cout << "setting tree[300] to '#'" << std::endl;
  // tree[300] = '#';
  // std::cout << "tree[300] = " << tree[300] << std::endl;
  // std::cout << "Size = " << tree.size() << std::endl;
  // puts("\n");

  // tree.displayTree(Order::elementsOnly);
  // puts("\n");

  puts("\n");

  return 0;
}
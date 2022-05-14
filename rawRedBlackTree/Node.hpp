#ifndef NODE_HPP
#define NODE_HPP

#include <utility>

const bool red = true;
const bool black = false;
const bool leftChild = true;
const bool rightChild = false;

template <typename K, typename V>
struct Node {
  std::pair<K, V> kvp;
  Node* left;
  Node* right;
  Node* parent;
  bool color;
  bool branch;
  Node(K _key, V _val, Node* _parent, bool _branch)
      : kvp{_key, _val}, left{nullptr}, right{nullptr}, color{red} {
    branch = _branch;
    parent = _parent;
  }
  Node() {}
};

#endif
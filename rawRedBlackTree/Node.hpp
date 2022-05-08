#ifndef NODE_HPP
#define NODE_HPP

const bool red = true;
const bool black = false;
const bool leftChild = true;
const bool rightChild = false;

template <typename K, typename V>
struct Node {
  K key;
  V val;
  Node* left;
  Node* right;
  Node* parent;
  bool color;
  bool branch;
  Node(K _key, V _val, Node* _parent, bool _branch)
      : key{_key}, val{_val}, left{nullptr}, right{nullptr}, color{red} {
    branch = _branch;
    parent = _parent;
  }
  Node() {}
};

#endif
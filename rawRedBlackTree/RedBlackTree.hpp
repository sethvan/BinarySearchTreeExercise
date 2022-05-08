#ifndef _RED_BLACK_TREE_
#define _RED_BLACK_TREE_

#include <cassert>
#include <iostream>

#include "Node.hpp"

template <typename K, typename V>
class RedBlackTree {
 public:
  enum Order { inOrder, preOrder, postOrder, elementsOnly };

 private:
  Node<K, V>* root;
  size_t treeSize;
  Node<K, V>* insertNode(Node<K, V>* parent, K key, V val);
  void checkColor(Node<K, V>* node);
  void correctTree(Node<K, V>* node);
  void rotate(Node<K, V>* node);
  void leftRotate(Node<K, V>* node);       // grandparent
  void rightRotate(Node<K, V>* node);      // grandparent
  void leftRightRotate(Node<K, V>* node);  // grandparent
  void rightLeftRotate(Node<K, V>* node);  // grandparent
  int calculateHeight(Node<K, V>* node) const;
  void destroyNodes(Node<K, V>* node);
  void traverse(Node<K, V>* ptr, Order order) const;
  int getBlackNodes(Node<K, V>* node) const;
  Node<K, V>* findKey(Node<K, V>* node, K key) const;
  Node<K, V>* moveToLeaf(Node<K, V>* toBeRemoved);
  void fixUp(Node<K, V>* node, Node<K, V>* sibling);
  void lowMemDestruct();

 public:
  RedBlackTree() {
    root = nullptr;
    treeSize = 0;
  }
  ~RedBlackTree();
  void insert(K key, V val);
  int height() const;
  void displayTree(Order order) const;
  int blackNodes() const;
  bool contains(K key) const;
  void erase(K key);
  V& operator[](const K& key);
  size_t size() const;
  Node<K, V>* firstInOrder();  // root
  Node<K, V>* nextInOrder(Node<K, V>* node);
};

template <typename K, typename V>
size_t RedBlackTree<K, V>::size() const {
  return treeSize;
}

template <typename K, typename V>
RedBlackTree<K, V>::~RedBlackTree() {
  lowMemDestruct();
}

template <typename K, typename V>
void RedBlackTree<K, V>::destroyNodes(Node<K, V>* node) {
  if (node) {
    destroyNodes(node->left);
    destroyNodes(node->right);
    delete node;
  }
}

template <typename K, typename V>
void RedBlackTree<K, V>::insert(K key, V val) {
  if (root == nullptr) {
    Node<K, V>* node = new Node<K, V>(key, val, nullptr, leftChild);
    node->color = black;
    root = node;
    treeSize++;
    return;
  }
  insertNode(root, key, val);
}

template <typename K, typename V>
Node<K, V>* RedBlackTree<K, V>::insertNode(Node<K, V>* parent, K key, V val) {
  if (key == parent->key) return nullptr;
  Node<K, V>* node;
  if (key > parent->key) {
    if (!parent->right) {
      node = new Node<K, V>(key, val, parent, rightChild);
      parent->right = node;
      treeSize++;
    } else
      return insertNode(parent->right, key, val);
  } else {
    if (!parent->left) {
      node = new Node<K, V>(key, val, parent, leftChild);
      parent->left = node;
      treeSize++;
    } else
      return insertNode(parent->left, key, val);
  }
  if (node) checkColor(node);
  return node;
}

template <typename K, typename V>
void RedBlackTree<K, V>::checkColor(Node<K, V>* node) {
  if (node == root) return;
  assert(node);
  if (node->color == red && node->parent->color == red) correctTree(node);
  if (node == root) return;
  return checkColor(node->parent);
}

template <typename K, typename V>
void RedBlackTree<K, V>::correctTree(Node<K, V>* node) {
  Node<K, V>* aunt;
  if (node->parent->branch == leftChild)
    aunt = node->parent->parent->right;
  else
    aunt = node->parent->parent->left;
  if (aunt == nullptr || aunt->color == black) return rotate(node);
  if (aunt != nullptr) aunt->color = black;
  if (node->parent->parent != root) node->parent->parent->color = red;
  node->parent->color = black;
  return;
}

template <typename K, typename V>
void RedBlackTree<K, V>::rotate(Node<K, V>* node) {
  auto singleRotateColors = [&](Node<K, V>* aunt) {
    node->color = red;
    node->parent->color = black;
    if (aunt != nullptr) aunt->color = red;
  };
  auto doubleRotateColors = [&]() {
    node->color = black;
    node->left->color = red;
    node->right->color = red;
  };
  if (node->branch == leftChild) {
    if (node->parent->branch == leftChild) {
      rightRotate(node->parent->parent);
      singleRotateColors(node->parent->right);
      return;
    } else {
      rightLeftRotate(node->parent->parent);
      doubleRotateColors();
      return;
    }
  } else {
    if (node->parent->branch == rightChild) {
      leftRotate(node->parent->parent);
      singleRotateColors(node->parent->left);
      return;
    } else {
      leftRightRotate(node->parent->parent);
      doubleRotateColors();
      return;
    }
  }
}

template <typename K, typename V>
void RedBlackTree<K, V>::leftRotate(Node<K, V>* node) {
  Node<K, V>* temp = node->right;
  if (temp->right) temp->right->parent = temp;
  node->right = temp->left;
  if (node->right != nullptr) {
    node->right->parent = node;
    node->right->branch = rightChild;
  }
  if (node->parent == nullptr) {
    temp->parent = nullptr;
    temp->left = node;
    temp->left->parent = temp;
    root = temp;
  } else {
    temp->parent = node->parent;
    temp->left = node;
    if (node->branch == leftChild) {
      temp->branch = leftChild;
      temp->parent->left = temp;
    } else {
      temp->branch = rightChild;
      temp->parent->right = temp;
    }
  }
  node->parent = temp;
  node->branch = leftChild;
}

template <typename K, typename V>
void RedBlackTree<K, V>::rightRotate(Node<K, V>* node) {
  Node<K, V>* temp = node->left;
  assert(temp);
  if (temp->left) temp->left->parent = temp;
  node->left = temp->right;
  if (node->left != nullptr) {
    node->left->parent = node;
    node->left->branch = leftChild;
  }
  if (node->parent == nullptr) {
    temp->parent = nullptr;
    temp->right = node;
    temp->right->parent = temp;
    root = temp;
  } else {
    temp->parent = node->parent;
    temp->right = node;
    if (node->branch == rightChild) {
      temp->branch = rightChild;
      temp->parent->right = temp;
    } else {
      temp->branch = leftChild;
      temp->parent->left = temp;
    }
  }
  node->parent = temp;
  node->branch = rightChild;
}

template <typename K, typename V>
void RedBlackTree<K, V>::leftRightRotate(Node<K, V>* node) {
  leftRotate(node->left);
  rightRotate(node);
}

template <typename K, typename V>
void RedBlackTree<K, V>::rightLeftRotate(Node<K, V>* node) {
  rightRotate(node->right);
  leftRotate(node);
}

template <typename K, typename V>
int RedBlackTree<K, V>::height() const {
  if (root == nullptr) return 0;
  return calculateHeight(root) - 1;
}

template <typename K, typename V>
int RedBlackTree<K, V>::calculateHeight(Node<K, V>* node) const {
  if (node == nullptr) return 0;
  int leftHeight = calculateHeight(node->left) + 1;
  int rightHeight = calculateHeight(node->right) + 1;
  if (leftHeight > rightHeight) return leftHeight;
  return rightHeight;
}

template <typename K, typename V>
void RedBlackTree<K, V>::displayTree(RedBlackTree<K, V>::Order order) const {
  if (!root) {
    std::cout << "Node equals nullptr\n";
    return;
  }
  traverse(root, order);
}

template <typename K, typename V>
void RedBlackTree<K, V>::traverse(Node<K, V>* ptr,
                                  RedBlackTree<K, V>::Order order) const {
  // needs adjustment for non-int types
  if (order == inOrder) {
    if (ptr) {
      traverse(ptr->left, order);
      std::cout << ptr->key << "(" << (ptr->color == red ? "red" : "black")
                << ")(val=" << ptr->val << ")"
                << ", " << (ptr->left ? std::to_string(ptr->left->key) : "NILL")
                << ", "
                << (ptr->right ? std::to_string(ptr->right->key) : "NILL")
                << std::endl;
      traverse(ptr->right, order);
    }
  } else if (order == preOrder) {
    if (ptr) {
      std::cout << ptr->key << "(" << (ptr->color == red ? "red" : "black")
                << ")(val=" << ptr->val << ")"
                << ", " << (ptr->left ? std::to_string(ptr->left->key) : "NILL")
                << ", "
                << (ptr->right ? std::to_string(ptr->right->key) : "NILL")
                << std::endl;
      traverse(ptr->left, order);
      traverse(ptr->right, order);
    }
  } else if (order == postOrder) {
    if (ptr) {
      traverse(ptr->left, order);
      traverse(ptr->right, order);
      std::cout << ptr->key << "(" << (ptr->color == red ? "red" : "black")
                << ")(val=" << ptr->val << ")"
                << ", " << (ptr->left ? std::to_string(ptr->left->key) : "NILL")
                << ", "
                << (ptr->right ? std::to_string(ptr->right->key) : "NILL")
                << std::endl;
    }
  } else if (order == elementsOnly) {
    if (ptr) {
      traverse(ptr->left, order);
      std::cout << ptr->key << "(" << (ptr->color == red ? "red" : "black")
                << ")(val=" << ptr->val << ")"
                << ", ";
      traverse(ptr->right, order);
    }
  }
}

template <typename K, typename V>
int RedBlackTree<K, V>::getBlackNodes(Node<K, V>* node) const {
  if (node == nullptr) return 1;
  int leftBlackNodes = getBlackNodes(node->left);
  int rightBlackNodes = getBlackNodes(node->right);
  assert(leftBlackNodes == rightBlackNodes);
  if (node->color == black) ++leftBlackNodes;
  return leftBlackNodes;
}

template <typename K, typename V>
int RedBlackTree<K, V>::blackNodes() const {
  return getBlackNodes(root);
}

template <typename K, typename V>
Node<K, V>* RedBlackTree<K, V>::findKey(Node<K, V>* node, K key) const {
  if (node == nullptr) return nullptr;
  if (node->key == key) return node;
  if (key < node->key)
    return findKey(node->left, key);
  else
    return findKey(node->right, key);
}

template <typename K, typename V>
bool RedBlackTree<K, V>::contains(K key) const {
  return findKey(root, key) != nullptr;
}

template <typename K, typename V>
Node<K, V>* RedBlackTree<K, V>::moveToLeaf(Node<K, V>* toBeRemoved) {
  Node<K, V>* current = toBeRemoved;
  Node<K, V>* replacingWith = nullptr;
  auto swapAndMove = [&]() {
    std::swap(toBeRemoved->key, replacingWith->key);
    toBeRemoved = moveToLeaf(replacingWith);
  };

  if (!current->right && !current->left) {
    if (toBeRemoved->parent) {
      if (toBeRemoved->branch == leftChild)
        toBeRemoved->parent->left = nullptr;
      else
        toBeRemoved->parent->right = nullptr;
    }
    return toBeRemoved;
  } else if (!current->right) {
    replacingWith = current->left;
    swapAndMove();
  } else {
    if (!current->right->left) {
      replacingWith = current->right;
      swapAndMove();
    } else {
      current = current->right;
      while (current->left) current = current->left;
      replacingWith = current;
      swapAndMove();
    }
  }
  return toBeRemoved;
}

template <typename K, typename V>
void RedBlackTree<K, V>::erase(K key) {
  Node<K, V>* node;
  if ((node = findKey(root, key)) == nullptr) return;
  if ((node = moveToLeaf(node))->color == red || node == root) {
    if (node == root) root = nullptr;
    delete node;
    --treeSize;
    return;
  }
  Node<K, V>* sibling =
      node->branch == leftChild ? node->parent->right : node->parent->left;
  fixUp(node, sibling);
  delete node;
  --treeSize;
  return;
}

template <typename K, typename V>
void RedBlackTree<K, V>::fixUp(Node<K, V>* node, Node<K, V>* sibling) {
  if (node)
    if (node == root) return;

  Node<K, V>* parent = sibling->parent;
  if (sibling->color == red) {
    std::swap(parent->color, sibling->color);
    if (sibling->branch == leftChild) {
      rightRotate(parent);
      fixUp(node, parent->left);
    } else {
      leftRotate(parent);
      fixUp(node, parent->right);
    }
  } else {
    if ((!sibling->left || sibling->left->color == black) &&
        (!sibling->right || sibling->right->color == black)) {
      sibling->color = red;
      if (parent->color == red)
        parent->color = black;
      else {
        if (parent->parent) {
          if (parent->branch == leftChild)
            fixUp(parent, parent->parent->right);
          else
            fixUp(parent, parent->parent->left);
        }
        return;
      }
    } else {
      if (sibling->branch == rightChild) {
        if ((sibling->left && (sibling->left->color == red)) &&
            (!sibling->right || (sibling->right->color == black)))  // case 5
        {
          std::swap(sibling->left->color, sibling->color);
          rightRotate(sibling);
          sibling = sibling->parent;
        }
        if (sibling->right && (sibling->right->color == red))  // case 6
        {
          Node<K, V>* nephew = sibling->right;
          std::swap(sibling->parent->color, sibling->color);
          leftRotate(sibling->parent);
          nephew->color = black;
        }
      } else {
        if ((sibling->right && (sibling->right->color == red)) &&
            (!sibling->left || (sibling->left->color == black)))  // case 5
        {
          std::swap(sibling->right->color, sibling->color);
          leftRotate(sibling);
          sibling = sibling->parent;
        }
        if (sibling->left && (sibling->left->color == red))  // case 6
        {
          Node<K, V>* nephew = sibling->left;
          std::swap(sibling->parent->color, sibling->color);
          rightRotate(sibling->parent);
          nephew->color = black;
        }
      }
    }
  }
}

template <typename K, typename V>
V& RedBlackTree<K, V>::operator[](const K& key) {
  Node<K, V>* node;
  if ((node = findKey(root, key)) != nullptr)
    return node->val;
  else {
    V defaultVal{};
    if (!treeSize) {
      insert(key, defaultVal);
      return root->val;
    }
    node = insertNode(root, key, defaultVal);
    return node->val;
  }
}

template <typename K, typename V>
Node<K, V>* RedBlackTree<K, V>::firstInOrder()  // root
{
  Node<K, V>* node = root;
  while (node->left) node = node->left;
  return node;
}

template <typename K, typename V>
Node<K, V>* RedBlackTree<K, V>::nextInOrder(Node<K, V>* node) {
  if (node->right) {
    node = node->right;
    if (node->left)
      while (node->left) node = node->left;
    return node;
  }
  if (node->branch == leftChild) return node->parent;
  while (node->parent && (node->parent->branch == rightChild))
    node = node->parent;
  return node->parent == root || node == root ? nullptr : node->parent->parent;
}

template <typename K, typename V>
void RedBlackTree<K, V>::lowMemDestruct() {
  Node<K, V>* node = firstInOrder();
  while (root) {
    while (node->right) {
      node = node->right;
      if (node->left)
        while (node->left) node = node->left;
    }
    Node<K, V>* temp = node;
    node = node->parent;
    if (temp == root)
      root = nullptr;
    else {
      if (temp->branch == leftChild)
        node->left = nullptr;
      else
        node->right = nullptr;
    }
    delete temp;
  }
}

#endif  // RedBlackTree

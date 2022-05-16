#ifndef _RED_BLACK_TREE_
#define _RED_BLACK_TREE_

#include <cassert>
#include <iostream>
#include <iterator>
#include <memory>
#include <utility>

#include "Node.hpp"

template <typename K, typename V>
class RedBlackTree {
 public:
  struct Iterator {
    using value_type = std::pair<const K, V>;
    using difference_type = ptrdiff_t;
    using pointer = value_type*;
    using reference = value_type&;
    using iterator_category = std::bidirectional_iterator_tag;

   private:
    Node<K, V>* p;
    Node<K, V>* itRoot;
    Node<K, V>* nextInOrder();
    Node<K, V>* previousInOrder();
    Node<K, V>* lastInOrder();

   public:
    Iterator(Node<K, V>* _p = nullptr, Node<K, V>* _root = nullptr);
    Iterator& operator++();
    Iterator operator++(int);
    Iterator& operator--();
    Iterator operator--(int);
    bool operator!=(const Iterator& rhs) const;
    bool operator==(const Iterator& rhs) const;
    std::pair<const K&, V&> operator*();
    std::unique_ptr<std::pair<const K&, V&>> operator->();
  };

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
  Node<K, V>* firstInOrder();  // root
  void copyTree(Node<K, V>* rhsRoot);

 public:
  RedBlackTree() {
    root = nullptr;
    treeSize = 0;
  }
  RedBlackTree(const RedBlackTree<K, V>& rhs);
  RedBlackTree(RedBlackTree<K, V>&& rhs) noexcept;
  ~RedBlackTree();
  RedBlackTree<K, V>& operator=(const RedBlackTree<K, V>& rhs);
  RedBlackTree<K, V>& operator=(RedBlackTree<K, V>&& rhs) noexcept;

  bool empty() { return (!root); }
  void clear();
  void insert(K key, V val);
  int height() const;
  void displayTree(Order order) const;
  int blackNodes() const;
  bool contains(K key) const;
  void erase(K key);
  V& operator[](const K& key);
  size_t size() const;
  Iterator begin();
  Iterator end();
  void swap(RedBlackTree<K, V>& rhs) noexcept;
};

template <typename K, typename V>
RedBlackTree<K, V>::RedBlackTree(const RedBlackTree<K, V>& rhs)
    : RedBlackTree() {
  copyTree(rhs.root);
}

template <typename K, typename V>
RedBlackTree<K, V>::RedBlackTree(RedBlackTree<K, V>&& rhs) noexcept {
  root = rhs.root;
  treeSize = rhs.size();
  rhs.treeSize = 0;
  rhs.root = nullptr;
}

template <typename K, typename V>
RedBlackTree<K, V>& RedBlackTree<K, V>::operator=(
    const RedBlackTree<K, V>& rhs) {
  RedBlackTree<K, V> temp(rhs);
  swap(temp);
  return *this;
}

template <typename K, typename V>
RedBlackTree<K, V>& RedBlackTree<K, V>::operator=(
    RedBlackTree<K, V>&& rhs) noexcept {
  RedBlackTree<K, V> temp(std::move(rhs));
  swap(temp);
  return *this;
}

template <typename K, typename V>
void RedBlackTree<K, V>::copyTree(Node<K, V>* rhsRoot) {
  if (rhsRoot) {
    this->insert(rhsRoot->kvp.first, rhsRoot->kvp.second);
    copyTree(rhsRoot->left);
    copyTree(rhsRoot->right);
  }
}

template <typename K, typename V>
size_t RedBlackTree<K, V>::size() const {
  return treeSize;
}

template <typename K, typename V>
RedBlackTree<K, V>::~RedBlackTree() {
  if (root) lowMemDestruct();
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
void RedBlackTree<K, V>::clear() {
  Node<K, V>* temp = root;
  root = nullptr;
  destroyNodes(temp);
  treeSize = 0;
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
  if (key == parent->kvp.first) return nullptr;
  Node<K, V>* node;
  if (key > parent->kvp.first) {
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
      std::cout << ptr->kvp.first << "("
                << (ptr->color == red ? "red" : "black")
                << ")(val=" << ptr->kvp.second << ")"
                << ", "
                << (ptr->left ? std::to_string(ptr->left->kvp.first) : "NILL")
                << ", "
                << (ptr->right ? std::to_string(ptr->right->kvp.first) : "NILL")
                << std::endl;
      traverse(ptr->right, order);
    }
  } else if (order == preOrder) {
    if (ptr) {
      std::cout << ptr->kvp.first << "("
                << (ptr->color == red ? "red" : "black")
                << ")(val=" << ptr->kvp.second << ")"
                << ", "
                << (ptr->left ? std::to_string(ptr->left->kvp.first) : "NILL")
                << ", "
                << (ptr->right ? std::to_string(ptr->right->kvp.first) : "NILL")
                << std::endl;
      traverse(ptr->left, order);
      traverse(ptr->right, order);
    }
  } else if (order == postOrder) {
    if (ptr) {
      traverse(ptr->left, order);
      traverse(ptr->right, order);
      std::cout << ptr->kvp.first << "("
                << (ptr->color == red ? "red" : "black")
                << ")(val=" << ptr->kvp.second << ")"
                << ", "
                << (ptr->left ? std::to_string(ptr->left->kvp.first) : "NILL")
                << ", "
                << (ptr->right ? std::to_string(ptr->right->kvp.first) : "NILL")
                << std::endl;
    }
  } else if (order == elementsOnly) {
    if (ptr) {
      traverse(ptr->left, order);
      std::cout << ptr->kvp.first << "("
                << (ptr->color == red ? "red" : "black")
                << ")(val=" << ptr->kvp.second << ")"
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
  if (node->kvp.first == key) return node;
  if (key < node->kvp.first)
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
    std::swap(toBeRemoved->kvp, replacingWith->kvp);
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
    return node->kvp.second;
  else {
    V defaultVal{};
    if (!treeSize) {
      insert(key, defaultVal);
      return root->kvp.second;
    }
    node = insertNode(root, key, defaultVal);
    return node->kvp.second;
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

template <typename K, typename V>
RedBlackTree<K, V>::Iterator RedBlackTree<K, V>::begin() {
  if (root) return Iterator{firstInOrder(), root};
}

template <typename K, typename V>
RedBlackTree<K, V>::Iterator RedBlackTree<K, V>::end() {
  if (root) return Iterator{root->parent, root};
}

template <typename K, typename V>
void RedBlackTree<K, V>::swap(RedBlackTree<K, V>& rhs) noexcept {
  Node<K, V>* tempRoot = rhs.root;
  size_t tempSize = rhs.treeSize;
  rhs.root = root;
  rhs.treeSize = treeSize;
  root = tempRoot;
  treeSize = tempSize;
  tempRoot = nullptr;
}

/***************************Iterator methods*****************************/

template <typename K, typename V>
RedBlackTree<K, V>::Iterator::Iterator(Node<K, V>* _p, Node<K, V>* _root)
    : p{_p}, itRoot(_root) {
  if (!itRoot) {
    Node<K, V>* node = p;
    while (node->parent) node = node->parent;
    itRoot = node;
  }
}

template <typename K, typename V>
Node<K, V>* RedBlackTree<K, V>::Iterator::nextInOrder() {
  if (p) {
    if (p->right) {
      p = p->right;
      if (p->left)
        while (p->left) p = p->left;
      return p;
    }
    if (p->parent && (p->parent->left == p)) return p->parent;
    while (p->parent && (p->parent->right == p)) p = p->parent;
    return p->parent;
  }
  return p;
}

template <typename K, typename V>
Node<K, V>* RedBlackTree<K, V>::Iterator::previousInOrder() {
  if (p) {
    if (p->left) {
      p = p->left;
      if (p->right)
        while (p->right) p = p->right;
      return p;
    }
    if (p->parent && p->parent->right == p) return p->parent;
    while (p->parent && (p->parent->left == p)) p = p->parent;
    return !p->parent ? p->parent : p->parent->parent;
  }
  return nullptr;
}

template <typename K, typename V>
Node<K, V>* RedBlackTree<K, V>::Iterator::lastInOrder()  // root
{
  Node<K, V>* node = itRoot;
  while (node->right) node = node->right;
  return node;
}

template <typename K, typename V>
RedBlackTree<K, V>::Iterator& RedBlackTree<K, V>::Iterator::operator++() {
  p = nextInOrder();
  return *this;
}

template <typename K, typename V>
RedBlackTree<K, V>::Iterator RedBlackTree<K, V>::Iterator::operator++(int) {
  auto temp = *this;
  p = nextInOrder();
  return temp;
}

template <typename K, typename V>
RedBlackTree<K, V>::Iterator& RedBlackTree<K, V>::Iterator::operator--() {
  p = p == nullptr ? lastInOrder() : previousInOrder();
  return *this;
}

template <typename K, typename V>
RedBlackTree<K, V>::Iterator RedBlackTree<K, V>::Iterator::operator--(int) {
  auto temp = *this;
  p = p == nullptr ? lastInOrder() : previousInOrder();
  return temp;
}

template <typename K, typename V>
bool RedBlackTree<K, V>::Iterator::operator!=(
    const RedBlackTree<K, V>::Iterator& rhs) const {
  if (itRoot) return p != rhs.p;
}

template <typename K, typename V>
bool RedBlackTree<K, V>::Iterator::operator==(
    const RedBlackTree<K, V>::Iterator& rhs) const {
  return p == rhs.p;
}

template <typename K, typename V>
std::unique_ptr<std::pair<const K&, V&>>
RedBlackTree<K, V>::Iterator::operator->() {
  auto constKeyPairPtr = [&](const K& key, V& value) {
    return std::make_unique<std::pair<const K&, V&>>(key, value);
  };
  return constKeyPairPtr(p->kvp.first, p->kvp.second);
}

template <typename K, typename V>
std::pair<const K&, V&> RedBlackTree<K, V>::Iterator::operator*() {
  if (itRoot) {
    auto constKeyPair = [&](const K& key, V& value) {
      return std::pair<const K&, V&>(key, value);
    };
    return constKeyPair(p->kvp.first, p->kvp.second);
  }
}

#endif  // RedBlackTree

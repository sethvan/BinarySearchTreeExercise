// Raw version
#include "BinarySearchTree.hpp"

#include <iostream>
#include <memory>
BinarySearchTree::BinarySearchTree(const BinarySearchTree& rhs) {
  head = nullptr;
  copyTree(rhs.head);
}

BinarySearchTree::BinarySearchTree(BinarySearchTree&& rhs) noexcept {
  head = rhs.head;
  rhs.head = nullptr;
}

BinarySearchTree& BinarySearchTree::BinarySearchTree::operator=(
    const BinarySearchTree& rhs) {
  Node* temp = head;
  head = nullptr;
  copyTree(rhs.head);
  destroyNodes(temp);
  return *this;
}

BinarySearchTree& BinarySearchTree::BinarySearchTree::operator=(
    BinarySearchTree&& rhs) noexcept {
  Node* temp = head;
  head = rhs.head;
  rhs.head = nullptr;
  destroyNodes(temp);
  return *this;
}

BinarySearchTree::~BinarySearchTree() { destroyNodes(head); }

void BinarySearchTree::copyTree(Node* rhsHead) {
  if (rhsHead) {
    this->insert(rhsHead->val);
    copyTree(rhsHead->left);
    copyTree(rhsHead->right);
  }
}

void BinarySearchTree::destroyNodes(Node* p) {
  if (p) {
    destroyNodes(p->left);
    destroyNodes(p->right);
    delete p;
  }
}

void BinarySearchTree::insertNode(Node** ptr, int n) {
  if (*ptr == nullptr) {
    *ptr = new Node{n, nullptr, nullptr};
    return;
  } else {
    if (n < (*ptr)->val) {
      ptr = &((*ptr)->left);
      insertNode(ptr, n);
    } else if (n > (*ptr)->val) {
      ptr = &((*ptr)->right);
      insertNode(ptr, n);
    } else
      return;
  }
}

void BinarySearchTree::insert(int n) { insertNode(&head, n); }

std::optional<BinarySearchTree::lookupResult> BinarySearchTree::foundInList(
    Node* parent, Node* node, int n, bool left) {
  if (node == nullptr) {
    return std::nullopt;
  } else if (node->val == n) {
    return std::optional<BinarySearchTree::lookupResult>{{node, parent, left}};
  } else {
    if (n < node->val) {
      return foundInList(node, node->left, n, true);
    } else {
      return foundInList(node, node->right, n, false);
    }
  }
}

bool BinarySearchTree::contains(int n) {
  auto s = foundInList(head, head, n, true);
  return s != std::nullopt;
}

void BinarySearchTree::displayTree(BinarySearchTree::Order order) const {
  if (!head) {
    std::cout << "Node equals nullptr\n";
    return;
  }
  traverse(head, order);
}

void BinarySearchTree::traverse(Node* ptr,
                                BinarySearchTree::Order order) const {
  if (order == inOrder) {
    if (ptr) {
      traverse(ptr->left, order);
      std::cout << ptr->val << ", "
                << (ptr->left ? std::to_string(ptr->left->val) : "NULL") << ", "
                << (ptr->right ? std::to_string(ptr->right->val) : "NULL")
                << std::endl;
      traverse(ptr->right, order);
    }
  } else if (order == preOrder) {
    if (ptr) {
      std::cout << ptr->val << ", "
                << (ptr->left ? std::to_string(ptr->left->val) : "NULL") << ", "
                << (ptr->right ? std::to_string(ptr->right->val) : "NULL")
                << std::endl;
      traverse(ptr->left, order);
      traverse(ptr->right, order);
    }
  } else if (order == postOrder) {
    if (ptr) {
      traverse(ptr->left, order);
      traverse(ptr->right, order);
      std::cout << ptr->val << ", "
                << (ptr->left ? std::to_string(ptr->left->val) : "NULL") << ", "
                << (ptr->right ? std::to_string(ptr->right->val) : "NULL")
                << std::endl;
    }
  } else if (order == elementsOnly) {
    if (ptr) {
      traverse(ptr->left, order);
      std::cout << ptr->val << ", ";
      traverse(ptr->right, order);
    }
  }
}

void BinarySearchTree::erase(int n) {
  std::optional<lookupResult> s = foundInList(head, head, n, true);
  if (!s) return;

  Node* toBeRemoved = head->val == n ? head : s->node;
  Node* current = toBeRemoved;
  Node* replacingWith = nullptr;
  auto leftOrRight = [&]() {
    if (s->left) {
      s->parent->left = replacingWith;
    } else {
      s->parent->right = replacingWith;
    }
  };

  if (!current->right && !current->left) {
    if (head->val != n) leftOrRight();
    delete toBeRemoved;
    return;
  } else if (!current->right) {
    replacingWith = current->left;
  } else {
    if (!current->right->left) {
      replacingWith = current->right;
      replacingWith->left = toBeRemoved->left;
    } else {
      current = current->right;
      while (current->left->left) current = current->left;
      Node* rwParent = current;  // parent of replacingWith
      replacingWith = rwParent->left;
      rwParent->left = replacingWith->right;
      replacingWith->left = toBeRemoved->left;
      replacingWith->right = toBeRemoved->right;
    }
  }
  if (head->val != n)
    leftOrRight();
  else
    head = replacingWith;

  toBeRemoved->left = nullptr;
  toBeRemoved->right = nullptr;
  delete toBeRemoved;
}

bool BinarySearchTree::empty() { return (!head); }

int BinarySearchTree::size() {
  elementQty = 0;
  calculateSize(head);
  return elementQty;
}

void BinarySearchTree::calculateSize(Node* ptr) {
  if (ptr) {
    calculateSize(ptr->left);
    if (ptr->val) ++elementQty;
    calculateSize(ptr->right);
  }
}

void BinarySearchTree::clear() {
  Node* temp = head;
  head = nullptr;
  destroyNodes(temp);
}

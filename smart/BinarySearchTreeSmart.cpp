#include "BinarySearchTreeSmart.hpp"

#include <iostream>
#include <string>

BinarySearchTreeSmart::BinarySearchTreeSmart(const BinarySearchTreeSmart& rhs) {
  head = nullptr;
  copyTree(rhs.head.get());
}

BinarySearchTreeSmart::BinarySearchTreeSmart(
    BinarySearchTreeSmart&& rhs) noexcept {
  head = std::move(rhs.head);
  rhs.head = nullptr;
};

BinarySearchTreeSmart& BinarySearchTreeSmart::BinarySearchTreeSmart::operator=(
    const BinarySearchTreeSmart& rhs) {
  if (head == rhs.head) return *this;
  head = nullptr;
  copyTree(rhs.head.get());
  return *this;
}

BinarySearchTreeSmart& BinarySearchTreeSmart::BinarySearchTreeSmart::operator=(
    BinarySearchTreeSmart&& rhs) noexcept {
  if (head == rhs.head) return *this;
  head = std::move(rhs.head);
  rhs.head = nullptr;
  return *this;
};

BinarySearchTreeSmart::~BinarySearchTreeSmart() {
  destroyNodes(std::move(head));
};

void BinarySearchTreeSmart::copyTree(Node* rhsHead) {
  if (rhsHead) {
    this->insert(rhsHead->val);
    copyTree(rhsHead->left.get());
    copyTree(rhsHead->right.get());
  }
}

void BinarySearchTreeSmart::destroyNodes(std::unique_ptr<Node> p) {
  if (p) {
    destroyNodes(std::move(p->left));
    destroyNodes(std::move(p->right));
    p.reset(nullptr);
  }
}

void BinarySearchTreeSmart::insertNode(std::unique_ptr<Node>* ptr, int n) {
  if (*ptr == nullptr) {
    *ptr = std::make_unique<Node>(n, nullptr, nullptr);
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

void BinarySearchTreeSmart::insert(int n) { insertNode(&head, n); }

bool BinarySearchTreeSmart::foundInList(Node* ptr, int n) const {
  if (ptr == nullptr) {
    return false;
  } else if (ptr->val == n) {
    return true;
  } else {
    if (n < ptr->val) {
      ptr = ptr->left.get();
      return foundInList(ptr, n);
    } else {
      ptr = ptr->right.get();
      return foundInList(ptr, n);
    }
  }
}

bool BinarySearchTreeSmart::contains(int n) const {
  return foundInList(head.get(), n);
}

void BinarySearchTreeSmart::displayTree(
    BinarySearchTreeSmart::Order order) const {
  if (!head) {
    std::cout << "Node equals nullptr\n";
    return;
  }
  traverse(head.get(), order);
}

void BinarySearchTreeSmart::traverse(Node* ptr,
                                     BinarySearchTreeSmart::Order order) const {
  if (order == inOrder) {
    if (ptr) {
      traverse(ptr->left.get(), order);
      std::cout << ptr->val << ", "
                << (ptr->left ? std::to_string(ptr->left->val) : "NULL") << ", "
                << (ptr->right ? std::to_string(ptr->right->val) : "NULL")
                << std::endl;
      traverse(ptr->right.get(), order);
    }
  } else if (order == preOrder) {
    if (ptr) {
      std::cout << ptr->val << ", "
                << (ptr->left ? std::to_string(ptr->left->val) : "NULL") << ", "
                << (ptr->right ? std::to_string(ptr->right->val) : "NULL")
                << std::endl;
      traverse(ptr->left.get(), order);
      traverse(ptr->right.get(), order);
    }
  } else if (order == postOrder) {
    if (ptr) {
      traverse(ptr->left.get(), order);
      traverse(ptr->right.get(), order);
      std::cout << ptr->val << ", "
                << (ptr->left ? std::to_string(ptr->left->val) : "NULL") << ", "
                << (ptr->right ? std::to_string(ptr->right->val) : "NULL")
                << std::endl;
    }
  } else if (order == elementsOnly) {
    if (ptr) {
      traverse(ptr->left.get(), order);
      std::cout << ptr->val << ", ";
      traverse(ptr->right.get(), order);
    }
  }
}

size_t BinarySearchTreeSmart::size() {
  elementQty = 0;
  calculateSize(head.get());
  return elementQty;
}

void BinarySearchTreeSmart::calculateSize(Node* ptr) {
  if (ptr) {
    calculateSize(ptr->left.get());
    if (ptr->val) ++elementQty;
    calculateSize(ptr->right.get());
  }
}
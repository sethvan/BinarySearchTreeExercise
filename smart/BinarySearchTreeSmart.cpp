#include "BinarySearchTreeSmart.hpp"

#include <cassert>
#include <iostream>
#include <string>
#include <utility>

BinarySearchTreeSmart::BinarySearchTreeSmart(const BinarySearchTreeSmart& rhs)
    : BinarySearchTreeSmart() {
  copyTree(rhs.head.get());
}

BinarySearchTreeSmart::BinarySearchTreeSmart(
    BinarySearchTreeSmart&& rhs) noexcept
    : BinarySearchTreeSmart() {
  swap(rhs);
};

BinarySearchTreeSmart& BinarySearchTreeSmart::BinarySearchTreeSmart::operator=(
    const BinarySearchTreeSmart& rhs) {
  BinarySearchTreeSmart temp(rhs);
  swap(temp);
  return *this;
}

BinarySearchTreeSmart& BinarySearchTreeSmart::BinarySearchTreeSmart::operator=(
    BinarySearchTreeSmart&& rhs) noexcept {
  BinarySearchTreeSmart temp(std::move(rhs));
  swap(temp);
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

bool BinarySearchTreeSmart::contains(int n) {
  return foundInList(&head, &head, n, true) != std::nullopt;
}

void BinarySearchTreeSmart::displayTree(Order order) const {
  if (!head) {
    std::cout << "Node equals nullptr\n";
    return;
  }
  traverse(head.get(), order);
}

void BinarySearchTreeSmart::traverse(Node* ptr, Order order) const {
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

void BinarySearchTreeSmart::swap(BinarySearchTreeSmart& rhs) {
  std::swap(head, rhs.head);
}

bool BinarySearchTreeSmart::empty() const { return !head; }

void BinarySearchTreeSmart::clear() { destroyNodes(std::move(head)); }

std::optional<BinarySearchTreeSmart::lookupResult>
BinarySearchTreeSmart::foundInList(std::unique_ptr<Node>* parent,
                                   std::unique_ptr<Node>* node, int n,
                                   bool left) {
  if ((*node) == nullptr) {
    return std::nullopt;
  } else if ((*node)->val == n) {
    return std::optional<BinarySearchTreeSmart::lookupResult>{
        {node, parent, left}};
  } else {
    if (n < (*node)->val) {
      return foundInList(node, &((*node)->left), n, true);
    } else {
      return foundInList(node, &((*node)->right), n, false);
    }
  }
}

void BinarySearchTreeSmart::erase(int n) {
  std::optional<lookupResult> s = foundInList(&head, &head, n, true);
  if (!s) return;
  int headVal = head->val;
  std::unique_ptr<Node> toBeRemoved =
      headVal == n ? std::move(head) : std::move(*(s->node));
  std::unique_ptr<Node>* current = &toBeRemoved;
  std::unique_ptr<Node> replacingWith = nullptr;
  auto leftOrRight = [&]() {
    if (s->left) {
      (*(s->parent))->left = std::move(replacingWith);
    } else {
      (*(s->parent))->right = std::move(replacingWith);
    }
  };

  if (!(*current)->right && !(*current)->left) {
    if (headVal != n) leftOrRight();
    toBeRemoved.reset();
    return;
  } else if (!(*current)->right) {
    replacingWith = std::move((*current)->left);
  } else {
    if (!(*current)->right->left) {
      replacingWith = std::move((*current)->right);
      replacingWith->left = std::move(toBeRemoved->left);
    } else {
      current = &((*current)->right);
      while ((*current)->left->left) current = &((*current)->left);
      replacingWith = std::move((*current)->left);
      (*current)->left = std::move(replacingWith->right);
      replacingWith->left = std::move(toBeRemoved->left);
      replacingWith->right = std::move(toBeRemoved->right);
    }
  }

  if (headVal != n)
    leftOrRight();
  else
    head = std::move(replacingWith);

  toBeRemoved->left.reset();
  toBeRemoved->right.reset();
  toBeRemoved.reset();
}
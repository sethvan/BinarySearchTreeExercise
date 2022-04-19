//Raw version
#include "BinarySearchTree.hpp"
#include <iostream>

BinarySearchTree::BinarySearchTree(const BinarySearchTree& rhs) {
  head = nullptr;
  copyTree(rhs.head);
}

BinarySearchTree::BinarySearchTree(BinarySearchTree&& rhs) noexcept{
  head = rhs.head;
  rhs.head = nullptr;
};

BinarySearchTree& BinarySearchTree::BinarySearchTree::operator=(const BinarySearchTree& rhs) {
  Node* temp = head;
  head = nullptr;
  copyTree(rhs.head);
  destroyNodes(temp);
  return *this;
}

BinarySearchTree& BinarySearchTree::BinarySearchTree::operator=(BinarySearchTree&& rhs) noexcept {
  Node* temp = head;
  head = rhs.head;
  rhs.head = nullptr;
  destroyNodes(temp);
  return *this;
};

BinarySearchTree::~BinarySearchTree() {
  destroyNodes(head);
};

void BinarySearchTree::copyTree(Node* rhsHead) {
  if(rhsHead) {
    this->insert(rhsHead->val);
    copyTree(rhsHead->left);
    copyTree(rhsHead->right);
  }
}

void BinarySearchTree::destroyNodes(Node*p) {
  if(p){
    destroyNodes(p->left);
    destroyNodes(p->right);
    delete p;
  }
}

void BinarySearchTree::insertNode(Node** ptr, int n) {
  if(*ptr == nullptr) {
    *ptr = new Node{n, nullptr, nullptr};
    return;
  } else {
    if (n < (*ptr)->val) {
      ptr = &((*ptr)->left);
      insertNode(ptr, n);
    } else if ( n > (*ptr)->val) {
      ptr = &((*ptr)->right);
      insertNode(ptr, n);
    } else return;
  }
}

void BinarySearchTree::insert(int n) {
  insertNode(&head, n);
}

bool BinarySearchTree::foundInList(Node* ptr, int n) const {
  if(ptr == nullptr) {    
    return false;
  } else if(ptr->val == n) {
    return true;
  } else {
    if (n < ptr->val) {
      ptr = ptr->left;
      return foundInList(ptr, n);
    } else {
      ptr = ptr->right;
      return foundInList(ptr, n);
    } 
  }
}

bool BinarySearchTree::contains(int n) const {
  return foundInList(head, n);
}

void BinarySearchTree::displayTree(const std::string& order) const {
  if(!head) {
    std::cout << "Node equals nullptr\n";
    return;
  }
  traverse(head, order);
}

void BinarySearchTree::traverse(Node* ptr, const std::string& order) const {
  
  if ( order == "inOrder" ) {
    if(ptr){
    traverse(ptr->left, order);
    std::cout << ptr->val << ", " << ( ptr->left ? std::to_string(ptr->left->val) : "NULL") << ", "
              << (ptr->right ? std::to_string(ptr->right->val) : "NULL") << std::endl;
    traverse(ptr->right, order);
    }
  } else if ( order == "preOrder") {
    if(ptr){
    std::cout << ptr->val << ", " << ( ptr->left ? std::to_string(ptr->left->val) : "NULL") << ", "
              << (ptr->right ? std::to_string(ptr->right->val) : "NULL") << std::endl;
    traverse(ptr->left, order);
    traverse(ptr->right, order);
    }
  } else if ( order == "postOrder") {
    if(ptr){
    traverse(ptr->left, order);
    traverse(ptr->right, order);
    std::cout << ptr->val << ", " << ( ptr->left ? std::to_string(ptr->left->val) : "NULL") << ", "
              << (ptr->right ? std::to_string(ptr->right->val) : "NULL") << std::endl;
   
    }
  } else if ( order == "elementsOnly" ) {
    if(ptr){
    traverse(ptr->left, order);
    std::cout << ptr->val << ", ";
    traverse(ptr->right, order);
    }
  } 
}
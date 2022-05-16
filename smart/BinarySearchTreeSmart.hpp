// Smart version
#ifndef _BINARY_SEARCH_TREE_SMART_
#define _BINARY_SEARCH_TREE_SMART_
#include <memory>
#include <string>

class BinarySearchTreeSmart {
  struct Node {
    int val;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
  };

 public:
  enum Order { inOrder, preOrder, postOrder, elementsOnly };

 private:
  std::unique_ptr<Node> head;
  void insertNode(std::unique_ptr<Node>* ptr, int n);
  bool foundInList(Node* ptr, int n) const;
  void destroyNodes(std::unique_ptr<Node> ptr);
  void traverse(Node* ptr, const Order order) const;
  void copyTree(Node* rhsHead);
  void calculateSize(Node* ptr);
  size_t elementQty{};

 public:
  BinarySearchTreeSmart() { head = nullptr; }
  BinarySearchTreeSmart(const BinarySearchTreeSmart& rhs);
  BinarySearchTreeSmart(BinarySearchTreeSmart&& rhs) noexcept;
  ~BinarySearchTreeSmart();
  BinarySearchTreeSmart& operator=(const BinarySearchTreeSmart& rhs);
  BinarySearchTreeSmart& operator=(BinarySearchTreeSmart&& rhs) noexcept;

  void displayTree(const Order order) const;
  void insert(int n);
  bool contains(int n) const;
  size_t size();
};

#endif  // Binary Search Tree
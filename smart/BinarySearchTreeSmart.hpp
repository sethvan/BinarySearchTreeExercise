// Smart version
#ifndef _BINARY_SEARCH_TREE_SMART_
#define _BINARY_SEARCH_TREE_SMART_
#include <memory>
#include <optional>
#include <string>

#include "../Order.hpp"

class BinarySearchTreeSmart {
  struct Node {
    int val;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
    Node(int _val, std::unique_ptr<Node> _left, std::unique_ptr<Node> _right)
        : val{_val}, left{std::move(_left)}, right{std::move(_right)} {}
  };

  struct lookupResult {
    std::unique_ptr<Node>* node;
    std::unique_ptr<Node>* parent;
    bool left;
  };

 private:
  std::unique_ptr<Node> head;
  void insertNode(std::unique_ptr<Node>* ptr, int n);

  void destroyNodes(std::unique_ptr<Node> ptr);
  void traverse(Node* ptr, const Order order) const;
  void copyTree(Node* rhsHead);
  void calculateSize(Node* ptr);
  size_t elementQty{};
  void swap(BinarySearchTreeSmart& rhs);
  std::optional<lookupResult> foundInList(std::unique_ptr<Node>* parent,
                                          std::unique_ptr<Node>* node, int n,
                                          bool left);

 public:
  BinarySearchTreeSmart() { head = nullptr; }
  BinarySearchTreeSmart(const BinarySearchTreeSmart& rhs);
  BinarySearchTreeSmart(BinarySearchTreeSmart&& rhs) noexcept;
  ~BinarySearchTreeSmart();
  BinarySearchTreeSmart& operator=(const BinarySearchTreeSmart& rhs);
  BinarySearchTreeSmart& operator=(BinarySearchTreeSmart&& rhs) noexcept;

  void displayTree(const Order order) const;
  void insert(int n);
  bool contains(int n);
  size_t size();
  bool empty() const;
  void clear();
  void erase(int n);
};

#endif  // Binary Search Tree
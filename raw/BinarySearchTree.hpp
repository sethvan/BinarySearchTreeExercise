// Raw version
#ifndef _BINARY_SEARCH_TREE_
#define _BINARY_SEARCH_TREE_
#include <optional>
#include <string>

class BinarySearchTree {
  struct Node {
    int val;
    Node* left;
    Node* right;
  };

  struct lookupResult {
    Node* node;
    Node* parent;
    bool left;
  };

 public:
  enum Order { inOrder, preOrder, postOrder, elementsOnly };

 private:
  Node* head;
  void insertNode(Node** ptr, int n);
  std::optional<lookupResult> foundInList(Node* parent, Node* node, int n,
                                          bool left);
  void destroyNodes(Node* ptr);
  void traverse(Node* ptr, Order order) const;
  void copyTree(Node* rhsHead);
  void calculateSize(Node* ptr);
  int elementQty{};

 public:
  BinarySearchTree() { head = nullptr; }
  BinarySearchTree(const BinarySearchTree& rhs);
  BinarySearchTree(BinarySearchTree&& rhs) noexcept;
  ~BinarySearchTree();
  BinarySearchTree& operator=(const BinarySearchTree& rhs);
  BinarySearchTree& operator=(BinarySearchTree&& rhs) noexcept;

  void displayTree(Order order) const;
  void insert(int n);
  bool contains(int n);
  void erase(int n);
  bool empty();
  int size();
  void clear();
};

#endif  // Binary Search Tree
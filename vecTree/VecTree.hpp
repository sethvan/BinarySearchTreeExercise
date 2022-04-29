#ifndef _VECTREE_H_
#define _VECTREE_H_

#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>

template <typename T>
class VecTree
{
   struct Node
   {
      int parent;
      std::unique_ptr<T> data;
      int left;
      int right;
      
      Node(Node &&rhs) noexcept 
      : parent{rhs.parent}, data{std::move(rhs.data)}, left{rhs.left}, right{rhs.right} {}

      Node(int parent, const T& element_data) 
      : parent {parent}, data{std::make_unique<T>(element_data)}, 
        left{-1}, right{-1} {}   
      Node& operator=(Node &&rhs) noexcept {
        parent = rhs.parent;
        data = std::move(rhs.data);
        left = rhs.left;
        right = rhs.right;
        return *this;
      }
   };

   private:
      int head;
      std::vector<Node> children;
      void insertNode(const T& element_data, int index);
      int foundIndex(int index, const T& element_data) const;
      void traverse(int index, const std::string& order ) const;


   public:
      VecTree() { head = -1; /*children.reserve(20000000);*/}
      void insert(const T& element_data);
      bool contains(const T& element_data) const;
      bool empty() const;
      int size() const;
      void clear();      
      void displayTree(const std::string& order) const;
      void erase(const T& element_data);
};

template <typename T>
bool VecTree<T>::empty() const {
  return head != -1;
}

template <typename T>
void VecTree<T>::clear() {
  children.clear();
}

template <typename T>
int VecTree<T>::size() const {
  if(children.size() == 0) return 0;

  int size {};
  for(const auto& node: children)
    if(node.data)
      ++size;
  return size;
}

template <typename T>
void VecTree<T>::displayTree(const std::string& order) const {
  traverse(head, order);
}

template <typename T>
bool VecTree<T>::contains(const T& element_data) const {
  return foundIndex(head, element_data) != -1;
}

template <typename T>
int VecTree<T>::foundIndex(int index, const T& element_data) const {
  if(index == -1) return -1;     
  else if(element_data == *(children[index].data))
    return index;
  else if(element_data < *(children[index].data))
  {
    if(children[index].left != -1 && children[index].left > children.size()-1)
      throw std::out_of_range("******Index in foundIndex() out of range!!!!******");      
    return foundIndex(children[index].left, element_data);
  }      
  else
  {
    if(children[index].right != -1 && children[index].right > children.size()-1)
      throw std::out_of_range("******Index in foundIndex() out of range!!!!******");      
    return foundIndex(children[index].right, element_data);
  }      
}

template <typename T>
void VecTree<T>::insert(const T& element_data) {
  if(head != -1) 
    insertNode(element_data, head);
  else 
    children.emplace_back(-1, element_data);
    head = 0;
}

template <typename T>
void VecTree<T>::insertNode(const T& element_data, int index) {
  int num, childIndex;

  if (element_data < *(children[index].data)) 
  {
    num = children[index].left;
    if(num != -1) 
      insertNode(element_data, num);
    else if( num == -1)
    {
      childIndex = children.size();
      children.emplace_back(index, element_data);
      children[index].left = childIndex;
    }
  } 
  else if (element_data > *(children[index].data))
    {
      num = children[index].right;
      if(num != -1)  
        insertNode(element_data, num);
      else if( num == -1) 
      {
        childIndex = children.size();
        children.emplace_back(index, element_data);
        children[index].right = childIndex;
      }
    } 
    else
      return;
}

template <typename T>
void VecTree<T>::erase(const T& element_data) {
 
  int toBeRemoved = foundIndex(head, element_data);
  if(toBeRemoved == -1) return;

  if(*(children[toBeRemoved].data) != element_data)
    throw std::runtime_error("**********foundIndex() has provided an incorrect index!!!!**********");
 
  int current = toBeRemoved;
  int tbrParent = children[toBeRemoved].parent;// parent of toBeRemoved
  int replacingWith = -1;
  int lastIndex = children.size()-1;

  auto setParentChild = [&](int* PARENT_HAND, int PARENT, int CHILD) {
    if((*PARENT_HAND = CHILD) != -1)
        children[CHILD].parent = PARENT;
  };

  auto leftOrRight = [&](){
    if(children[tbrParent].left == toBeRemoved) 
      setParentChild(&children[tbrParent].left, tbrParent, replacingWith);
    else if(children[tbrParent].right == toBeRemoved) 
      setParentChild(&children[tbrParent].right, tbrParent, replacingWith);
    else
      throw std::runtime_error("**************Parent is wrong!!**************");
  };

  auto deleteElement = [&](){
    if(toBeRemoved != lastIndex)
    {// Move vec.back() to element being removed and pop_back() the vec.back() element that is now empty
      auto itMoveMe = children.end()-1;
      int moveMeParent = itMoveMe->parent;
      auto itPlaceHere = children.begin()+toBeRemoved;
      *itPlaceHere = std::move(*itMoveMe);
      children.pop_back();
      
      if(children[moveMeParent].left == lastIndex)
        children[moveMeParent].left = toBeRemoved;
      else
        children[moveMeParent].right = toBeRemoved;
       
      if(children[toBeRemoved].left != -1)
        children[children[toBeRemoved].left].parent = toBeRemoved;
      if(children[toBeRemoved].right != -1)
        children[children[toBeRemoved].right].parent = toBeRemoved;
    }
    else
      children.pop_back();    
  };

  if(children[current].right == -1 && children[current].left == -1)
  {
    if(head != toBeRemoved) 
      leftOrRight();
    deleteElement();
    return;
  }
  else if(children[current].right == -1)
    replacingWith = children[current].left;
  else
  {
    if(children[children[current].right].left == -1) 
    {
      replacingWith = children[current].right;
      setParentChild(&children[replacingWith].left, replacingWith, children[toBeRemoved].left);
    }
    else
    {
      current = children[current].right;
      while(children[children[current].left].left != -1) current = children[current].left;      
      replacingWith = children[current].left;
      setParentChild(&children[current].left, current, children[replacingWith].right);
      setParentChild(&children[replacingWith].left, replacingWith, children[toBeRemoved].left);
      setParentChild(&children[replacingWith].right, replacingWith, children[toBeRemoved].right);
    }
  }
  if(head != toBeRemoved) 
    leftOrRight();
  else
    head = replacingWith;
  deleteElement();  
}

template <typename T>
void VecTree<T>::traverse(int index, const std::string& order ) const {
  if(!size())
  {
    std::cout << "Tree empty!" << std::endl;
    return;
  }
  auto printNodeValues = [&](){
    std::cout << *(children[index].data) << ", ";
    if(children[index].left != -1) std::cout << *(children[children[index].left].data) << ", ";
    else std::cout << "NULL" << ", ";
    if(children[index].right != -1) std::cout << *(children[children[index].right].data) << std::endl;
    else std::cout << "NULL" << ", " << std::endl;
  };

  if(index != -1) 
  {
    if ( order == "inOrder" ) 
    {
      traverse(children[index].left, order);
      printNodeValues();
      traverse(children[index].right, order);
    } 
    else if ( order == "preOrder") 
    {
      printNodeValues();
      traverse(children[index].left, order);
      traverse(children[index].right, order);
    } 
    else if ( order == "postOrder") 
    {
      traverse(children[index].left, order);
      traverse(children[index].right, order);
      printNodeValues();   
    } 
    else if ( order == "elementsOnly" ) 
    {
      traverse(children[index].left, order);
      std::cout << *(children[index].data) << ", ";
      traverse(children[index].right, order);
    } 
  }
}

#endif //VecTree
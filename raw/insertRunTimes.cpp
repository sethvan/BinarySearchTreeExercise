#include <iostream>
#include "BinarySearchTree.hpp"
#include <cstdlib>
#include <chrono>
#include <set>
#include "../smart/BinarySearchTreeSmart.hpp"
#include "../vecTree/VecTree.hpp"



//took this class from a google search :)
class Timer
{
private:
	// Type aliases to make accessing nested type easier
	using clock_type = std::chrono::steady_clock;
	using second_type = std::chrono::duration<double, std::ratio<1> >;

	std::chrono::time_point<clock_type> m_beg { clock_type::now() };

public:
	void reset()
	{
		m_beg = clock_type::now();
	}

	double elapsed() const
	{
		return std::chrono::duration_cast<second_type>(clock_type::now() - m_beg).count();
	}
};


int main(){

  int MAX = 6000000;//random number range
  int INSERT_ITERATIONS = 6000000;
  int REMOVE_ITERATIONS = 3000000; 
  srand(time(0));

  Timer t;
  BinarySearchTree tree0;
  for(int i {}; i < INSERT_ITERATIONS; ++i) {
    tree0.insert(rand()%MAX + 1);
  }
  auto timeElapsed = t.elapsed();
  
  std::cout << "\n" << timeElapsed << " seconds have elapsed for the raw binary search tree to insert " 
            << INSERT_ITERATIONS << " random numbers between 1 and " << MAX << "." << std::endl;
  std::cout << "Size of raw binary search tree = " << tree0.size() << std::endl;
  //tree0.displayTree("elementsOnly");
  
  Timer t1;
  std::set<int> setTree;
  for(int i {}; i < INSERT_ITERATIONS; ++i) {
    setTree.insert(rand()%MAX + 1);
  }
  auto timeElapsed1 = t1.elapsed();
  
  std::cout << "\n" << timeElapsed1 << " seconds have elapsed for the std::set<int> to insert " 
            << INSERT_ITERATIONS << " random numbers between 1 and " << MAX << "." << std::endl;
  std::cout << "Size of std::set<int> = " << setTree.size() << std::endl;

  Timer t2;
  BinarySearchTreeSmart tree1;
  for(int i {}; i < INSERT_ITERATIONS; ++i) {
    tree1.insert(rand()%MAX + 1);
  }
  auto timeElapsed2 = t2.elapsed();
  
  std::cout << "\n" << timeElapsed2 << " seconds have elapsed for the smart binary search tree to insert " 
            << INSERT_ITERATIONS << " random numbers between 1 and " << MAX << "." << std::endl;
  //std::cout << "Size of smart binary search tree = " << tree1.size() << std::endl;
  //tree1.displayTree("elementsOnly");
  
  Timer t8;
  VecTree<int> vecTree;
  for(int i {}; i < INSERT_ITERATIONS; ++i) {
    vecTree.insert(rand()%MAX + 1);
  }
  auto timeElapsed8 = t8.elapsed();
  
  std::cout << "\n" << timeElapsed8 << " seconds have elapsed for the vecTree to insert " 
            << INSERT_ITERATIONS << " random numbers between 1 and " << MAX << "." << std::endl;
  std::cout << "Size of vecTree = " << vecTree.size() << std::endl;
  //vecTree.displayTree("elementsOnly");

  // Timer t3;
  // for(int i {}; i < REMOVE_ITERATIONS; ++i) {
  //   tree0.erase(rand()%MAX + 1);     
  // }
  // auto timeElapsed3 = t3.elapsed();

  // std::cout << "\n" << timeElapsed3 << " seconds have elapsed for the raw binary search tree to erase " 
  //           << REMOVE_ITERATIONS << " random numbers between 1 and " << MAX << "." << std::endl;
  // std::cout << "Size of raw binary search tree after deletions = " << tree0.size() << "." << std::endl;
  
  // Timer t4;
  // for(int i {}; i < REMOVE_ITERATIONS; ++i) {
  //   setTree.erase(rand()%MAX + 1);  
  // }
  // auto timeElapsed4 = t4.elapsed();

  // std::cout << "\n" << timeElapsed4 << " seconds have elapsed for the setTree to erase " 
  //           << REMOVE_ITERATIONS << " random numbers between 1 and " << MAX << "." << std::endl;
  // std::cout << "Size of setTree after deletions = " << setTree.size() << "."<< std::endl;

  // Timer t10;
  // for(int i {}; i < REMOVE_ITERATIONS; ++i) {
  //   vecTree.erase(rand()%MAX + 1);  
  // }
  // auto timeElapsed10 = t10.elapsed();

  // std::cout << "\n" << timeElapsed10 << " seconds have elapsed for the vecTree to erase " 
  //           << REMOVE_ITERATIONS << " random numbers between 1 and " << MAX << "." << std::endl;
  // std::cout << "Size of vecTree after deletions = " << vecTree.size() << ".\n\n"<< std::endl;
  //vecTree.displayTree("elementsOnly");

  Timer t5;
  for(int i {}; i < REMOVE_ITERATIONS; ++i) {
    auto found = tree0.contains(rand()%MAX + 1);     
  }
  auto timeElapsed5 = t5.elapsed();

  std::cout << "\n" << timeElapsed5 << " seconds have elapsed for the raw binary search tree to search for " 
            << REMOVE_ITERATIONS << " random numbers between 1 and " << MAX << "." << std::endl;
  std::cout << "Size of raw binary search tree = " << tree0.size() << "." << std::endl;
  
  Timer t6;
  for(int i {}; i < REMOVE_ITERATIONS; ++i) {
    auto found = setTree.contains(rand()%MAX + 1);  
  }
  auto timeElapsed6 = t6.elapsed();

  std::cout << "\n" << timeElapsed6 << " seconds have elapsed for the setTree to search for " 
            << REMOVE_ITERATIONS << " random numbers between 1 and " << MAX << "." << std::endl;
  std::cout << "Size of setTree after = " << setTree.size() << "."<< std::endl;

  Timer t7;
  for(int i {}; i < REMOVE_ITERATIONS; ++i) {
    auto found = tree1.contains(rand()%MAX + 1);     
  }
  auto timeElapsed7 = t7.elapsed();

  std::cout << "\n" << timeElapsed7 << " seconds have elapsed for the smart binary search tree to search for " 
            << REMOVE_ITERATIONS << " random numbers between 1 and " << MAX << "." << std::endl;

   Timer t9;
  for(int i {}; i < REMOVE_ITERATIONS; ++i) {
    auto found = vecTree.contains(rand()%MAX + 1);     
  }
  auto timeElapsed9 = t9.elapsed();

  std::cout << "\n" << timeElapsed9 << " seconds have elapsed for the vecTree to search for " 
            << REMOVE_ITERATIONS << " random numbers between 1 and " << MAX << "." << std::endl;
  std::cout << "Size of vecTree = " << vecTree.size() << "." << std::endl;
  
  
  return 0;

}
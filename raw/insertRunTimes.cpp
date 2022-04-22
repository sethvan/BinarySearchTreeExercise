#include <iostream>
#include "BinarySearchTree.hpp"
#include <cstdlib>
#include <chrono>
#include <set>
#include "../smart/BinarySearchTreeSmart.hpp"


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

  int MAX = 100000000;//random number range
  int INSERT_ITERATIONS = 10000000;
  int REMOVE_ITERATIONS = 8000000; 
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
  
  Timer t1;
  std::set<int> setTree;
  for(int i {}; i < INSERT_ITERATIONS; ++i) {
    setTree.insert(rand()%MAX + 1);
  }
  auto timeElapsed1 = t1.elapsed();
  
  std::cout << "\n" << timeElapsed1 << " seconds have elapsed for the std::set<int> to insert " 
            << INSERT_ITERATIONS << " random numbers between 1 and " << MAX << "." << std::endl;
  std::cout << "Size of std::set<int> = " << setTree.size() << std::endl;

  // Timer t2;
  // BinarySearchTreeSmart tree1;
  // for(int i {}; i < INSERT_ITERATIONS; ++i) {
  //   tree1.insert(rand()%MAX + 1);
  // }
  // auto timeElapsed2 = t2.elapsed();
  
  // std::cout << "\n" << timeElapsed << " seconds have elapsed for the smart binary search tree to insert " 
  //           << INSERT_ITERATIONS << " random numbers between 1 and " << MAX << "." << std::endl;

  Timer t3;
  for(int i {}; i < REMOVE_ITERATIONS; ++i) {
    tree0.erase(rand()%MAX + 1);     
  }
  auto timeElapsed3 = t3.elapsed();

  std::cout << "\n" << timeElapsed3 << " seconds have elapsed for the raw binary search tree to erase " 
            << REMOVE_ITERATIONS << " random numbers between 1 and " << MAX << "." << std::endl;
  std::cout << "Size of raw binary search tree after deletions = " << tree0.size() << "." << std::endl;
  
  Timer t4;
  for(int i {}; i < REMOVE_ITERATIONS; ++i) {
    setTree.erase(rand()%MAX + 1);  
  }
  auto timeElapsed4 = t4.elapsed();

  std::cout << "\n" << timeElapsed4 << " seconds have elapsed for the setTree to erase " 
            << REMOVE_ITERATIONS << " random numbers between 1 and " << MAX << "." << std::endl;
  std::cout << "Size of setTree after deletions = " << setTree.size() << ".\n\n"<< std::endl;
  
  return 0;

}
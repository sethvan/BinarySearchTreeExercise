#include <iostream>
#include "BinarySearchTree.hpp"
#include <cstdlib>
#include <chrono>
#include <set>
#include "../smart/BinarySearchTreeSmart.hpp"

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

  int MAX = 20000000;
  srand(time(0));

  Timer t;
  BinarySearchTree tree0;
  for(int i {}; i < 20000000; ++i) {
    tree0.insert(rand()%MAX + 1);
  }
  auto timeElapsed = t.elapsed();

  std::cout << "\n" << timeElapsed << " seconds have elapsed for the raw Binary Search Tree." << std::endl;

  Timer t1;
  std::set<int> setTree;
  for(int i {}; i < 20000000; ++i) {
    setTree.insert(rand()%MAX + 1);
  }
  auto timeElapsed1 = t1.elapsed();
  
  std::cout << timeElapsed1 << " seconds have elapsed for the std:set<int>." << std::endl;

  Timer t2;
  BinarySearchTreeSmart tree1;
  for(int i {}; i < 20000000; ++i) {
    tree1.insert(rand()%MAX + 1);
  }
  auto timeElapsed2 = t2.elapsed();
  
  std::cout << timeElapsed2 << " seconds have elapsed for the Smart Binary Search Tree.\n" << std::endl;

  
  return 0;

}
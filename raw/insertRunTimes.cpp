#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <map>
#include <set>

#include "../rawRedBlackTree/RedBlackTree.hpp"
#include "../smart/BinarySearchTreeSmart.hpp"
#include "../vecTree/VecTree.hpp"
#include "BinarySearchTree.hpp"

// took this class from a google search :)
class Timer {
 private:
  // Type aliases to make accessing nested type easier
  using clock_type = std::chrono::steady_clock;
  using second_type = std::chrono::duration<double, std::ratio<1> >;

  std::chrono::time_point<clock_type> m_beg{clock_type::now()};

 public:
  void reset() { m_beg = clock_type::now(); }

  double elapsed() const {
    return std::chrono::duration_cast<second_type>(clock_type::now() - m_beg)
        .count();
  }
};

int main() {
  int MAX = 60000000;  // random number range
  int INSERT_ITERATIONS = 6000000;
  int REMOVE_ITERATIONS = 3000000;
  srand(time(0));

  // BinarySearchTree tree0;
  // Timer t;
  // for (int i{}; i < INSERT_ITERATIONS; ++i) {
  //   tree0.insert(rand() % MAX + 1);
  // }
  // auto timeElapsed = t.elapsed();

  // std::cout << "\n"
  //           << timeElapsed
  //           << " seconds have elapsed for the raw binary search tree to
  //           insert "
  //           << INSERT_ITERATIONS << " random numbers between 1 and " << MAX
  //           << "." << std::endl;
  // std::cout << "Size of raw binary search tree = " << tree0.size() <<
  // std::endl;

  std::map<int, int> stdMAP;
  Timer t1;
  for (int i{}; i < INSERT_ITERATIONS; ++i) {
    stdMAP[(rand() % MAX + 1)] = i;
  }
  auto timeElapsed1 = t1.elapsed();

  std::cout << "\n"
            << timeElapsed1
            << " seconds have elapsed for the std::map<int,int> to insert "
            << INSERT_ITERATIONS << " random numbers between 1 and " << MAX
            << "." << std::endl;
  std::cout << "Size of std::map<int,int> = " << stdMAP.size() << std::endl;

  // BinarySearchTreeSmart tree1;
  // Timer t2;
  // for (int i{}; i < INSERT_ITERATIONS; ++i) {
  //   tree1.insert(rand() % MAX + 1);
  // }
  // auto timeElapsed2 = t2.elapsed();

  // std::cout
  //     << "\n"
  //     << timeElapsed2
  //     << " seconds have elapsed for the smart binary search tree to insert "
  //     << INSERT_ITERATIONS << " random numbers between 1 and " << MAX << "."
  //     << std::endl;

  RedBlackTree<int, int> RBT;
  Timer t12;
  for (int i{}; i < INSERT_ITERATIONS; ++i) {
    RBT[(rand() % MAX + 1)] = i;
  }
  auto timeElapsed12 = t12.elapsed();

  std::cout << "\n"
            << timeElapsed12
            << " seconds have elapsed for the RedBlackTree to insert "
            << INSERT_ITERATIONS << " random numbers between 1 and " << MAX
            << "." << std::endl;
  std::cout << "Size of RedBlackTree = " << RBT.size() << std::endl;

  // VecTree<int> vecTree;
  // Timer t8;
  // for (int i{}; i < INSERT_ITERATIONS; ++i) {
  //   vecTree.insert(rand() % MAX + 1);
  // }
  // auto timeElapsed8 = t8.elapsed();

  // std::cout << "\n"
  //           << timeElapsed8
  //           << " seconds have elapsed for the vecTree to insert "
  //           << INSERT_ITERATIONS << " random numbers between 1 and " << MAX
  //           << "." << std::endl;
  // std::cout << "Size of vecTree = " << vecTree.size() << std::endl;

  // Timer t3;
  // for (int i{}; i < REMOVE_ITERATIONS; ++i) {
  //   tree0.erase(rand() % MAX + 1);
  // }
  // auto timeElapsed3 = t3.elapsed();

  // std::cout << "\n"
  //           << timeElapsed3
  //           << " seconds have elapsed for the raw binary search tree to erase
  //           "
  //           << REMOVE_ITERATIONS << " random numbers between 1 and " << MAX
  //           << "." << std::endl;
  // std::cout << "Size of raw binary search tree after deletions = "
  //           << tree0.size() << "." << std::endl;

  Timer t4;
  for (int i{}; i < REMOVE_ITERATIONS; ++i) {
    stdMAP.erase(rand() % MAX + 1);
  }
  auto timeElapsed4 = t4.elapsed();

  std::cout << "\n"
            << timeElapsed4
            << " seconds have elapsed for the std::map<int,int> to erase "
            << REMOVE_ITERATIONS << " random numbers between 1 and " << MAX
            << "." << std::endl;
  std::cout << "Size of std::map<int,int> after deletions = " << stdMAP.size()
            << "." << std::endl;

  // Timer t10;
  // for (int i{}; i < REMOVE_ITERATIONS; ++i) {
  //   vecTree.erase(rand() % MAX + 1);
  // }
  // auto timeElapsed10 = t10.elapsed();

  // std::cout << "\n"
  //           << timeElapsed10
  //           << " seconds have elapsed for the vecTree to erase "
  //           << REMOVE_ITERATIONS << " random numbers between 1 and " << MAX
  //           << "." << std::endl;
  // std::cout << "Size of vecTree after deletions = " << vecTree.size() << "."
  //           << std::endl;

  Timer t14;
  for (int i{}; i < REMOVE_ITERATIONS; ++i) {
    RBT.erase(rand() % MAX + 1);
  }
  auto timeElapsed14 = t14.elapsed();

  std::cout << "\n"
            << timeElapsed14
            << " seconds have elapsed for the rawRedBlackTree to erase "
            << REMOVE_ITERATIONS << " random numbers between 1 and " << MAX
            << "." << std::endl;
  std::cout << "Size of rawRedBlackTree after deletions = " << RBT.size()
            << ".\n\n"
            << std::endl;
  RBT.blackNodes();

  // int foundInRaw {};
  // bool found;
  // Timer t5;
  // for(int i {}; i < REMOVE_ITERATIONS; ++i) {
  //   if ((found = tree0.contains(rand()%MAX + 1))) ++foundInRaw;
  // }
  // auto timeElapsed5 = t5.elapsed();

  // std::cout << "\n" << timeElapsed5 << " seconds have elapsed for the raw
  // binary search tree to search for "
  //           << REMOVE_ITERATIONS << " random numbers between 1 and " << MAX
  //           << "." << std::endl;
  // std::cout << "Size of raw binary search tree = " << tree0.size() << "." <<
  // std::endl; std::cout << foundInRaw << " elements were found and " <<
  // REMOVE_ITERATIONS-foundInRaw << " were not found in the raw binary search
  // tree" << std::endl;

  int foundInSet{};
  Timer t6;
  for (int i{}; i < REMOVE_ITERATIONS; ++i) {
    if (stdMAP.contains(rand() % MAX + 1)) ++foundInSet;
  }
  auto timeElapsed6 = t6.elapsed();

  std::cout << "\n"
            << timeElapsed6
            << " seconds have elapsed for the std::map<int,int> to search for "
            << REMOVE_ITERATIONS << " random numbers between 1 and " << MAX
            << "." << std::endl;
  std::cout << "Size of std::map<int,int> after = " << stdMAP.size() << "."
            << std::endl;
  std::cout << foundInSet << " elements were found and "
            << REMOVE_ITERATIONS - foundInSet
            << " were not found in the std::map<int,int>" << std::endl;

  // int foundInSmart {};
  // Timer t7;
  // for(int i {}; i < REMOVE_ITERATIONS; ++i) {
  //   if( tree1.contains(rand()%MAX + 1) ) ++foundInSmart;
  // }
  // auto timeElapsed7 = t7.elapsed();

  // std::cout << "\n" << timeElapsed7 << " seconds have elapsed for the smart
  // binary search tree to search for "
  //           << REMOVE_ITERATIONS << " random numbers between 1 and " << MAX
  //           << "." << std::endl;
  // std::cout << foundInSmart << " elements were found and " <<
  // REMOVE_ITERATIONS-foundInSmart << " were not found in the smart binary
  // search tree" << std::endl;

  // int foundInVec {};
  // Timer t9;
  // for(int i {}; i < REMOVE_ITERATIONS; ++i) {
  //   if( vecTree.contains(rand()%MAX + 1) ) ++foundInVec;
  // }
  // auto timeElapsed9 = t9.elapsed();

  // std::cout << "\n" << timeElapsed9 << " seconds have elapsed for the vecTree
  // to search for "
  //           << REMOVE_ITERATIONS << " random numbers between 1 and " << MAX
  //           << "." << std::endl;
  // std::cout << "Size of vecTree = " << vecTree.size() << "." << std::endl;
  // std::cout << foundInVec << " elements were found and " <<
  // REMOVE_ITERATIONS-foundInVec << " were not found in the vecTree" <<
  // std::endl;

  int foundInRBT{};
  Timer t13;
  for (int i{}; i < REMOVE_ITERATIONS; ++i) {
    if (RBT.contains(rand() % MAX + 1)) ++foundInRBT;
  }
  auto timeElapsed13 = t13.elapsed();

  std::cout << "\n"
            << timeElapsed13
            << " seconds have elapsed for the rawRedBlackTree to search for "
            << REMOVE_ITERATIONS << " random numbers between 1 and " << MAX
            << "." << std::endl;
  std::cout << "Size of rawRedBlackTree = " << RBT.size() << "." << std::endl;
  std::cout << foundInRBT << " elements were found and "
            << REMOVE_ITERATIONS - foundInRBT
            << " were not found in the rawRedBlackTree" << std::endl;

  int divBy = 11;
  int numSet{};
  Timer t16;
  numSet = std::count_if(
      stdMAP.begin(), stdMAP.end(),
      [&](std::pair<int, int> pair) { return pair.second % divBy == 0; });
  auto timeElapsed16 = t16.elapsed();

  std::cout << "\n"
            << timeElapsed16
            << " seconds have elapsed for the std::map<int,int> to count "
            << numSet << " amount of numbers divisible by " << divBy << "."
            << std::endl;
  std::cout << "Size of std::map<int,int>  = " << stdMAP.size() << "."
            << std::endl;

  int numRBT{};
  Timer t15;
  numRBT = std::count_if(RBT.begin(), RBT.end(), [&](std::pair<int, int> pair) {
    return pair.second % divBy == 0;
  });
  auto timeElapsed15 = t15.elapsed();

  std::cout << "\n"
            << timeElapsed15
            << " seconds have elapsed for the rawRedBlackTree to count "
            << numRBT << " amount of numbers divisible by " << divBy << "."
            << std::endl;
  std::cout << "Size of rawRedBlackTree  = " << RBT.size() << "." << std::endl;

  return 0;
}
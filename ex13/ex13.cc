// Zicheng He 1534763 zicheh@uw.edu
// Copyright ©2018 Zicheng He.  All rights reserved.
// This modified version of original code can fix the memory leaks.
// For the first part, I changed the int pointer to unique_ptr of int.
// For the second part, I changeg v from a pointer to an int vector
// to a unique_ptr of int vetor.
// For the third part, I changed v2 and all the other int pointerss in
// it to unique_ptr of ints.
/*
 * Copyright ©2018 Hal Perkins.  All rights reserved.  Permission is
 * hereby granted to students registered for University of Washington
 * CSE 333 for use solely during Summer Quarter 2018 for purposes of
 * the course.  No other use, copying, distribution, or modification
 * is permitted without prior written consent. Copyrights for
 * third-party components of this work must be honored.  Instructors
 * interested in reusing these course materials should contact the
 * author.
 */
 
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

int main(int argc, char **argv) {
  // Allocate an integer on the heap, initialize to value 5.
  unique_ptr<int> x(new int(5));
  std::cout << "*x is: " << *x << std::endl;
 
  // Allocate a vector of integers on the heap, add some values to
  // that vector, sort the vector, print the values.
  unique_ptr<vector<int>> v(new vector<int>);
  v->push_back(13);
  v->push_back(42);
  v->push_back(17);
  std::sort(v->begin(), v->end());
  std::cout << "sorted v: ";
  for (int &el : *v) {
    std::cout << el << " ";
  }
  std::cout << std::endl;
 
  // Allocate a vector of (integer pointers) on the stack, add some
  // values to the vector from the heap, print the values.
  vector<unique_ptr<int>> v2;
  v2.push_back(unique_ptr<int>(new int(13)));
  v2.push_back(unique_ptr<int>(new int(42)));
  v2.push_back(unique_ptr<int>(new int(17)));
  std::cout << "unsorted v2: ";
  for (unique_ptr<int> &el : v2) {
    std::cout << *el << " ";
  }
  std::cout << std::endl;
 
  return EXIT_SUCCESS;
}

// Zicheng He 1534763 zicheh@uw.edu
// Copyright ©2018 Zicheng He.  All rights reserved.
// This script tests the IntPair object for its functionality, it will
// also check for if the object is passed by value or passed by reference
// when be used as a parameter
#include <cstdlib>
#include <iostream>
#include "IntPair.h"

// This function will change the value in the IntPair object, if the value
// of the IntPair in the main is changed, then it is pass by reference.
void Test(IntPair pair) {
  int a, b;
  pair.Get(&a, &b);
  pair.Set(a + 1, b + 1);
}

int main(int argc, char** argv) {
  IntPair test_pair(5, 6);
  Test(test_pair);
  int a, b;
  test_pair.Get(&a, &b);
  
  std::cout << "Is pass by ";
  if (a == 5 && b == 6) {
    std::cout << "value";
  } else if (a == 6 && b == 7) {
    std::cout << "reference";
  }
  std::cout << std::endl;
  return EXIT_SUCCESS;
}

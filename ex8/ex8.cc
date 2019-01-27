// Zicheng He 1534763 zicheh@uw.edu
// Copyright ©2018 Zicheng He.  All rights reserved.
// This is a c++ script that can used for calculating the factors of a
// positive integer, after the script send a prompt the user types in
// a positive integer, then it will print out all the factors of it.
#include <cstdlib>
#include <iostream>
#include <cinttypes>

using namespace std;

// This function is used to calculate if divide is a factor of base.
// This function takes in 2 unsigned 64bit integer as parameter, return
// a boolean value indicating if divide is a factor.
bool isFactor(uint64_t base, uint64_t divide);

int main(int argc, char** argv) {
  cout << "Which positive integer would you like me to factorize? ";
  // use signed int here, to check if user puts in negative input
  int64_t in;
  cin >> in;

  // error case: input is not integer or input is less than or equal to 0
  if (!cin || in <= 0) {
    cerr << "Invalid input" << endl;
    return EXIT_FAILURE;
  }

  // save input number back to unsigned int
  uint64_t num = in;
  for (uint64_t i = 1; i <= num; i++) {
    if (isFactor(num, i)) {
      cout << i << " ";
    }
  }

  cout << endl;
  return EXIT_SUCCESS;
}

bool isFactor(uint64_t base, uint64_t factor) {
  if (base < factor) {  // prevent error case
    return false;
  }

  return (base % factor == 0);
}

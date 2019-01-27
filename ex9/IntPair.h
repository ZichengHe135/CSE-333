// Zicheng He 1534763 zicheh@uw.edu
// Copyright ©2018 Zicheng He.  All rights reserved.
// This is a header file for IntPair class, this class can store two
// integers in a pair, and has functions to get and change the integers
// in the object
#ifndef _INT_PAIR_H_
#define _INT_PAIR_H_

class IntPair {
  public:
  	// constructor, constructs a IntPair object with two integers as
  	// parameters
    IntPair(const int a, const int b);
    // get the content of a IntPair object and store them in two int
    // pointers
    void Get(int* a, int* b);
    // set the value of two ints in a IntPair object to a and b
    void Set(const int a, const int b);

  private:  // variables
    int a_;
    int b_;
};

#endif

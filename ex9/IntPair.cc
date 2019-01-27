// Zicheng He 1534763 zicheh@uw.edu
// Copyright ©2018 Zicheng He.  All rights reserved.
// This is an implementation of IntPair object
#include <iostream>
#include "IntPair.h"

// constructor
IntPair::IntPair(const int a, const int b) : a_(a), b_(b) {}

void IntPair::Get(int* a, int* b) {
  *a = a_;
  *b = b_;
}

void IntPair::Set(const int a, const int b) {
  a_ = a;
  b_ = b;
}

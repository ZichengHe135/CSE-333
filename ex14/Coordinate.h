// Zicheng He 1534763 zicheh@uw.edu
// Copyright ©2018 Zicheng He.  All rights reserved.
// This is the header file for coordinate, it is a super calss for
// any kinds of coordinate system, it is a pure virtual class, any
// sub class must at least implement a ToString method to work.
#ifndef _COORDINATE_H_
#define _COORDINATE_H_

#include <string>

using namespace std;

class Coordinate {
 public:
  virtual string ToString() const = 0;
};

#endif  // _COORDINATE_H_

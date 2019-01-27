// Zicheng He 1534763 zicheh@uw.edu
// Copyright ©2018 Zicheng He.  All rights reserved.
// This is the header file for polar class, it is a sub class for
// coordinate, it uses polar coordinates to implement, polar coordinates
// means to use angle and radius to represent the position of a point.
// this class's ToString method will print out its radius and angle, it
// also has a Distance method to calculate distance
#ifndef _POLAR_H_
#define _POLAR_H_

#include <string>
#include "./Coordinate.h"

using namespace std;

const double PI = 3.141592653589793238462643383279502884;

class Polar : public Coordinate {
 public:
  Polar(const double rad, const double ang);
  virtual ~Polar() {}
  virtual string ToString() const;
  virtual double Distance(const Polar& other);

 private:
  double rad_;
  double ang_;
};

#endif  // _POLAR_H_

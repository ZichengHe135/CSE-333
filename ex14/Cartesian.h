// Zicheng He 1534763 zicheh@uw.edu
// Copyright ©2018 Zicheng He.  All rights reserved.
// This is the header file for cartesian class, it is a sub class for
// coordinate, it uses cartesian coordinates to implement, it has a
// ToString implementation to print out x and y, and a distance
// calculation method to calculate the distance between two points
#ifndef _CARTESIAN_H_
#define _CARTESIAN_H_

#include <string>
#include "./Coordinate.h"

using namespace std;

class Cartesian : public Coordinate {
 public:
  Cartesian(const double x, const double y);
  virtual ~Cartesian() {}
  virtual string ToString() const;
  virtual double Distance(const Cartesian& other);

 private:
  double x_;
  double y_;
};

#endif  // _CARTESIAN_H_

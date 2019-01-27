// Zicheng He 1534763 zicheh@uw.edu
// Copyright ©2018 Zicheng He.  All rights reserved.
// This is an implementation of cartesian class
#include <cmath>
#include <string>
#include "./Cartesian.h"

using namespace std;

// construct the object with given coordinates
Cartesian::Cartesian(const double x, const double y) {
  x_ = x;
  y_ = y;
}

// return the point's position as a string
string Cartesian::ToString() const {
  return ("Cartesian(" + to_string(x_) + ", " + to_string(y_) + ")");
}

// calculate the distance between two points
double Cartesian::Distance(const Cartesian& other) {
  double base = other.x_ - x_;
  double height = other.y_ - y_;
  return sqrt(base*base + height*height);
}

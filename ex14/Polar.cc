// Zicheng He 1534763 zicheh@uw.edu
// Copyright ©2018 Zicheng He.  All rights reserved.
// This is an implementation of polar class
#include <cmath>
#include <string>
#include "./Polar.h"

using namespace std;

// This constructs a polar object with given radius and angle, note theat
// the angle should be in radians
Polar::Polar(const double rad, const double ang) {
  rad_ = rad;
  ang_ = ang;
}

// return the point's position as a string
string Polar::ToString() const {
  return ("Polar(radius=" + to_string(rad_) +
            ", angle=" + to_string(ang_) + ")");
}

// calculate the distance between two points
double Polar::Distance(const Polar& other) {
  double r1 = rad_;
  double r2 = other.rad_;
  double theta = ang_ - other.ang_;
  return sqrt(r1*r1+r2*r2-2*r1*r2*cos(theta));
}

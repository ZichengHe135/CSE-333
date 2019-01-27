// Zicheng He 1534763 zicheh@uw.edu
// Copyright ©2018 Zicheng He.  All rights reserved.
// This is an implementation of Vector class funtions, differ from ex10,
// this one allocates all the data on the heap
#include <iostream>
using namespace std;
#include "./Vector.h"

namespace vector333 {

// default constructor
Vector::Vector() {
  coord_ = new float[3];
  if (coord_ == nullptr) {
    cout << "Error: not enough memory" << endl;
    exit(EXIT_FAILURE);
  }
  coord_[0] = coord_[1] = coord_[2] = 0;
}

// constructor, assign three floats to x y z
Vector::Vector(const float x, const float y, const float z) {
  coord_ = new float[3];
  if (coord_ == nullptr) {
    cout << "Error: not enough memory" << endl;
    exit(EXIT_FAILURE);
  }
  coord_[0] = x;
  coord_[1] = y;
  coord_[2] = z;
}

// copy constructor
Vector::Vector(const Vector &other) {
  coord_ = new float[3];
  if (coord_ == nullptr) {
    cout << "Error: not enough memory" << endl;
    exit(EXIT_FAILURE);
  }
  coord_[0] = other.coord_[0];
  coord_[1] = other.coord_[1];
  coord_[2] = other.coord_[2];
}

// destrctor, free the data
Vector::~Vector() {
  delete coord_;
}

// overwrites v1 = v2
Vector &Vector::operator=(const Vector &other) {
  if (this != &other) {
    coord_[0] = other.coord_[0];
    coord_[1] = other.coord_[1];
    coord_[2] = other.coord_[2];
  }
  return *this;
}

// overwrites v1 += v2
Vector &Vector::operator+=(const Vector &other) {
  coord_[0] += other.coord_[0];
  coord_[1] += other.coord_[1];
  coord_[2] += other.coord_[2];
  return *this;
}

// overwrites v1 -= v2
Vector &Vector::operator-=(const Vector &other) {
  coord_[0] -= other.coord_[0];
  coord_[1] -= other.coord_[1];
  coord_[2] -= other.coord_[2];
  return *this;
}

// overwrites v1 * v2
double operator*(const Vector &a, const Vector &b) {
  double result = 0;
  result += a.coord_[0] * b.coord_[0];
  result += a.coord_[1] * b.coord_[1];
  result += a.coord_[2] * b.coord_[2];
  return result;
}

// overwrites k * v
Vector operator*(const double k, const Vector &v) {
  Vector temp(k * v.coord_[0], k * v.coord_[1], k * v.coord_[2]);
  return temp;
}

// overwrites v * k
Vector operator*(const Vector &v, const double k) {
  Vector temp(k * v.coord_[0], k * v.coord_[1], k * v.coord_[2]);
  return temp;
}

// overwrites << operator
ostream& operator<<(ostream &out, const Vector &v) {
  out << "(" << v.coord_[0] << "," << v.coord_[1] << "," << v.coord_[2] << ")";
  return out;
}

// overwrites v1 + v2
Vector operator+(const Vector &a, const Vector &b) {
  Vector temp = a;
  temp += b;
  return temp;
}

// overwrites v1 - v2
Vector operator-(const Vector &a, const Vector &b) {
  Vector temp = a;
  temp -= b;
  return temp;
}

}  // namespace vector333


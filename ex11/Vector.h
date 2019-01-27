// Zicheng He 1534763 zicheh@uw.edu
// Copyright ©2018 Zicheng He.  All rights reserved.
// This is the header file for Vector class, it implements
// a 3d vector
#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <iostream>
using namespace std;

namespace vector333 {

class Vector {
 public:
  // constructors
  // default
  Vector();
  Vector(const float x, const float y, const float z);
  // copy
  Vector(const Vector &other);

  // destructor
  ~Vector();

  // assignment
  Vector &operator=(const Vector &other);

  // updating assignment
  Vector &operator+=(const Vector &other);
  Vector &operator-=(const Vector &other);

  // multiplication
  // v * v
  friend double operator*(const Vector &a, const Vector &b);
  // k * v
  friend Vector operator*(const double k, const Vector &v);
  // v * k
  friend Vector operator*(const Vector &v, const double k);

  // stream output
  friend ostream& operator<<(ostream &out, const Vector &v);

 private:
  // member variable
  float* coord_;
};

// addition and subtraction
Vector operator+(const Vector &a, const Vector &b);
Vector operator-(const Vector &a, const Vector &b);

}  // namespace vector333

#endif  // _VECTOR_H_

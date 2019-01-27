// Zicheng He 1534763 zicheh@uw.edu
// Copyright ©2018 Zicheng He.  All rights reserved.
// This is the header file for Vector class
// NOTE: This class do not have any method for accessing data in public,
//       so all the operations involved should be either member function
//       or friendly global function.
#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <iostream>

namespace vector333 {

class Vector {
 public:
  // constructors
  Vector();  // defalut constructor
  Vector(const float x, const float y, const float z);
  Vector(const Vector& copyme);  // copy constructor

  // destructor
  ~Vector();

  // overload operators: =, +, -, +=, -=, *
  Vector& operator=(const Vector& other);
  // for + and -: The vector class we implement do not have any mean to
  //              access x, y, z outside, so they must be member functions
  Vector operator+(const Vector& other);
  Vector operator-(const Vector& other);
  Vector& operator+=(const Vector& other);
  Vector& operator-=(const Vector& other);
  // for * : This * operator here takes care of the case v*k, for the same
  //         reason above this must be a member function.
  //         The other case, k*v can only be handle as a friend function
  Vector operator*(const double k);
  // for * : This one is v1*v2
  float operator*(const Vector& other);

  // friend functions: These are the operators that do not start with a
  //                   vector object but needs to access private variables
  // for << : For the reason same as above, this overload needs to access
  //          private member variables, so it must be a freind function
  friend std::ostream& operator<<(std::ostream& os, const Vector& v);
  // for * : This function here implements the case k*v
  friend Vector operator*(const double k, const Vector &v);

 private:
  // member variables
  float x_;
  float y_;
  float z_;
};

}  // namespace vector333

#endif  // _VECTOR_H_

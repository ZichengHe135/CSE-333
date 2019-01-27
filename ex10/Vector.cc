// Zicheng He 1534763 zicheh@uw.edu
// Copyright ©2018 Zicheng He.  All rights reserved.
// This is an implementation of Vector class funtions
#include <iostream>

#include "Vector.h"

namespace vector333 {

// default constructor
Vector::Vector() : x_(0), y_(0), z_(0) {}

// constructor, assign three floats to x y z
Vector::Vector(const float x, const float y, const float z)
  : x_(x), y_(y), z_(z) {}

// copy constructor
Vector::Vector(const Vector& copyme) {
  x_ = copyme.x_;
  y_ = copyme.y_;
  z_ = copyme.z_;
}

// destructor
Vector::~Vector() {}

Vector& Vector::operator=(const Vector& other) {
  if (this != &other) {
    this->x_ = other.x_;
    this->y_ = other.y_;
    this->z_ = other.z_;
  }
  return *this;
}

Vector Vector::operator+(const Vector& other) {
  Vector temp;
  temp.x_ = this->x_ + other.x_;
  temp.y_ = this->y_ + other.y_;
  temp.z_ = this->z_ + other.z_;
  return temp;
}

Vector Vector::operator-(const Vector& other) {
  Vector temp;
  temp.x_ = this->x_ - other.x_;
  temp.y_ = this->y_ - other.y_;
  temp.z_ = this->z_ - other.z_;
  return temp;
}

Vector& Vector::operator+=(const Vector& other) {
  this->x_ += other.x_;
  this->y_ += other.y_;
  this->z_ += other.z_;
  return *this;
}

Vector& Vector::operator-=(const Vector& other) {
  this->x_ -= other.x_;
  this->y_ -= other.y_;
  this->z_ -= other.z_;
  return *this;
}

// using a vector to multiply a double
Vector Vector::operator*(const double k) {
  Vector temp;
  temp.x_ = this->x_ * k;
  temp.y_ = this->y_ * k;
  temp.z_ = this->z_ * k;
  return temp;
}

float Vector::operator*(const Vector& other) {
  float result = 0.0;
  result += this->x_ * other.x_;
  result += this->y_ * other.y_;
  result += this->z_ * other.z_;
  return result;
}

// write out the contents of the vector to std cout, in the
// form of "(x,y,z)"
std::ostream& operator<<(std::ostream& os, const Vector& v) {
  os << "(" << v.x_ << "," << v.y_ << "," << v.z_ << ")";
  return os;
}

// using a double to multiply a vector
Vector operator*(const double k, const Vector& v) {
  Vector temp;
  temp.x_ = v.x_ * k;
  temp.y_ = v.y_ * k;
  temp.z_ = v.z_ * k;
  return temp;
}

}  // namespace vector333


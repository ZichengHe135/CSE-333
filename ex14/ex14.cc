// Zicheng He 1534763 zicheh@uw.edu
// Copyright ©2018 Zicheng He.  All rights reserved.
// This is a test scrpt for Coordinate class and its subclasses.
#include <iostream>
#include "./Cartesian.h"
#include "./Polar.h"
#include "./Coordinate.h"

using namespace std;

int main(int argc, char** argv) {
  // test for cartesian class
  Cartesian* c1 = new Cartesian(5, 6);
  Cartesian* c2 = new Cartesian(2, 2);
  double dist = c1->Distance(*c2);
  cout << "expecting (5, 6)" << endl;
  cout << "actual point is " << c1->ToString() << endl;
  cout << "expecting 5" << endl;
  cout << "calculated distance is " << dist << endl;

  // test for polar class
  Polar* p1 = new Polar(1, PI/2);
  Polar* p2 = new Polar(2, PI/4);
  dist = p1->Distance(*p2);
  cout << "expecting (1, PI/2)" << endl;
  cout << "actual point is " << p1->ToString() << endl;
  cout << "expecting 1.473626" << endl;
  cout << "calculated distance is " << dist << endl;

  // test if the inheritence is working
  Coordinate* super = c2;
  cout << "expecting (2, 2)" << endl;
  cout << "actual point is " << super->ToString() << endl;

  delete(c1);
  delete(c2);
  delete(p1);
  delete(p2);
  return EXIT_SUCCESS;
}

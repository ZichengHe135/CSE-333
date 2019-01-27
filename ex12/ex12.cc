// Zicheng He 1534763 zicheh@uw.edu
// Copyright ©2018 Zicheng He.  All rights reserved.
// This script is used for sorting a list of 10 doubles
// it contains two template methods, one is ReadValue which will read one
// value of T from an in stream. The other is a compare method that will
// compare two  T values and return a bool value, intended for sorting
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// This method will read one value from in stream. When the value read is
// not a T type or is an eof it exits and print an error message.
template <class T> T ReadValue(istream& in) {
  T result;
  in >> result;
  if (in.eof()) {
    cout << "reach eof" << endl;
    exit(EXIT_FAILURE);
  } else if (!in) {
    cout << "bad format input" << endl;
    exit(EXIT_FAILURE);
  }
  return result;
}

// compare two T type values, if latter one is larger it returns true,
// vice versa.
template <class T>
bool comp(const T& a, const T& b) {
  return a < b;
}

int main(int argc, char **argv) {
  vector<double> buffer;
  cout << "Input 10 doubles:" << endl;

  // read the values into buffer
  for (int i = 0; i < 10; i++) {
    double element = ReadValue<double>(cin);
    buffer.push_back(element);
  }

  // sort the vector using comp
  sort(buffer.begin(), buffer.end(), comp<double>);
  cout << "Your sorted doubles are:" << endl;

  // print
  for (int i = 0; i < 10; i++) {
    cout << buffer[i] << endl;
  }

  return EXIT_SUCCESS;
}

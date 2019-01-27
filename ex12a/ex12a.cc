// Zicheng He 1534763 zicheh@uw.edu
// Copyright ©2018 Zicheng He.  All rights reserved.
// This script can be used to read a file and count the indifidual words
// in the file, and print out the list of words sorted and the numbers
// each word appeared.
#include <iostream>  // print
#include <fstream>  // read file
#include <map>  // store data

using namespace std;

int main(int argc, char **argv) {
  // check if we have a filename
  if (argc != 2) {
    cout << "wrong number of arguments" << endl;
    exit(EXIT_FAILURE);
  }
  char* filename = argv[1];

  ifstream f;
  f.open(filename);
  // check if file exists
  if (!f.is_open()) {
    cout << "file does not exist" << endl;
    exit(EXIT_FAILURE);
  }

  map<string, int> buf;
  string str;
  while (f >> str) {
    // check if the word read is good
    if (f.bad()) {
      cout << "bad input" << endl;
      exit(EXIT_FAILURE);
    }

    // use map.explace(), if the word haven't appeared, add it in with one
    // appearance. If it appeared before, the ret value pair will be
    // false, in that case we add the number of appearance by 1
    pair<map<string, int>::iterator, bool> ret;
    ret = buf.emplace(str, 1);
    if (!ret.second) {
      ret.first->second++;
    }
  }

  // print
  for (pair<string, int> p : buf) {
    cout << p.first << " " << p.second << endl;
  }

  // close file
  f.close();
  return EXIT_SUCCESS;
}

// Zicheng He 1534763 zicheh@uw.edu
// This code shows a method of checking if a datatype is pass by value or pass by reference.
// The data types checked in this script are char and array of floats. When a parameter is
// pass into another function and changed in that function, if the data type is pass by value,
// when it go back to the original function, the copy in the original function will not change.
// For the case of a pass by reference type parameter, the copy in the original function will
// change. This is basically the method this script used for compararing.
#include <stdio.h>
#include <stdlib.h>

static void ch_checker(char in);
static void ar_checker(float in[]);

int main(int argc, char* argv[]) {
  // initiating test data
  char ch_test = 'a';
  float ar_test[] = {1.0, 2.0};

  ch_checker(ch_test);
  ar_checker(ar_test);

  printf("char: ");
  if (ch_test == 'a') {
    printf("pass-by-value\n");
  } else {
    printf("pass-by-reference\n");
  }

  printf("array of floats: ");
  if ((ar_test[0] == 1.0) & (ar_test[1] == 2.0)) {
    printf("pass-by-value\n");
  } else {
    printf("pass-by-reference\n");
  }

  return 0;
}

// This function is used for checking if char is a pass by value type of a pass by reference type.
// It changes the value of the parameter inside this function.
static void ch_checker(char in) {
  in++;
}

// This function is used for checking if array of floats is a pass by value type of a pass by
// reference type. It changes the value of the parameter inside this function.
static void ar_checker(float in[]) {
  in++;
}

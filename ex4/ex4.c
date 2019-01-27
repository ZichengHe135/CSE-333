// Zicheng He 1534763 zicheh@uw.edu
// Copyright ©2018 Zicheng He.  All rights reserved.
// This script contains a series of tests for NthPrime.h, it will test
// the functionality of the algorithm and if it can handle error case
// properly.
#include "NthPrime.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int main(int argc, char **argv) {
  printf("Testing the functionality of NthPrime.c\n");

  // test1 tests for 1st, 4th and 10th prime number
  printf("test1: small valid input\n");
  if ((NthPrime(1) != 2) || (NthPrime(4) != 7) || (NthPrime(10) != 29)) {
    printf("test1 failed\n");
    return EXIT_FAILURE;
  } else {
    printf("passed!\n");
  }

  // test2 test for some random large prime number
  printf("test2: random large valid input\n");
  if ((NthPrime(1000) != 7919) || (NthPrime(1919) != 16573)) {
    printf("test2 failed\n");
    return EXIT_FAILURE;
  } else {
    printf("passed!\n");
  }

  // test3 test for invalid input, n is uint16_t type so it cannot be
  // negative or be larger than 65,535, the only invalid input case
  // is if n = 0. We expect a error message and a 0 here.
  printf("test3: invalid input\n");
  printf("  expecting: Error: invalid input\n  ");
  if (NthPrime(0) != 0) {
    printf("test3 failed\n");
    return EXIT_FAILURE;
  } else {
    printf("passed!\n");
  }

  // test4 test for the largest output possible which is 65535. Look up
  // a database I found the 65,535th prime number is 821,603. It is the
  // largest output our algorithm can get, it is smaller than 2^64 so
  // it does not exceed upper limit, which means in this case it should
  // return 821,603.
  printf("test4: largest input\n");
  if (NthPrime(65535) != 821603) {
    printf("test4 failed\n");
    return EXIT_FAILURE;
  } else {
    printf("passed!\n");
  }

  printf("all tests passed!\n");
  return EXIT_SUCCESS;
}

// Zicheng He 1534763 zicheh@uw.edu
// Copyright ©2018 Zicheng He.  All rights reserved.
// This is a script for NthPrime algorithm, it is used for finding
// the nth prime number starting from 2.
#include "NthPrime.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

// This is a helper method, it can calculate if one integer is a prime
// number or not. It takes in a 64 bit unsigned integer as parameter.
// The function returns 1 if the number is found to be a prime number,
// and return 0 if it is not.
int isPrime(uint64_t n) {
  for (int i = 2; (i * i) < (n + 1); i++) {
    if (n % i == 0) {
      return 0;
    }
  }
  return 1;
}

// This function can be used to find the nth prime number starting from
// 2. It takes in a unsigned 16 bit integer for parameter, as the
// index number of the prime number we want to find. The function returns
// a unsigned 64 bit integer as the output, which is the corresponding
// prime number.
// Error handling: if the input is illegal, the function returns a 0.
//                 if the output exceeds the limit for 64 bit unsigned
//                 integer, it returns and 1. Both cases will print out
//                 an error message.
uint64_t NthPrime(uint16_t n) {
  uint64_t result = 1;
  uint16_t count = 0;

  if ((n < 1) || (n > UINT16_MAX)) {
    printf("Error: invalid input\n");
    return 0;
  }

  while (count < n) {
    result++;
    if (isPrime(result)) {
      count++;
    }
    if (result >= UINT64_MAX) {
      printf("Error: the answer is too large\n");
      return 1;
    }
  }

  return result;
}

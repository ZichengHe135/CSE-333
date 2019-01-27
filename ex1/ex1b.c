// Zicheng He 1534763 zicheh@uw.edu
// This script implements a function that can copy an array into another array while sorting the
// elements in it from lowest to highest. The sorting function can sort arrays of 64 bit signed
// integers, it use insertion sort and run on O(n^2).
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

static void CopyAndSort(int64_t in[], int64_t out[], uint32_t size);
static void switcher(int64_t ar[], uint32_t position);

int main(int argc, char* argv[]) {
  // initiate the testing arrays
  int64_t original[] = {3, 2, -5, 7, 13, 4, 1, 7, 8, -8, 6};
  int64_t result[11] = {0};
  uint32_t size = 11;

  // sorting
  CopyAndSort(original, result, size);

  //print out the result
  for (uint32_t i = 0; i < size; i++) {
    printf("%" PRId64 " ", result[i]);
  }
  printf("\n");
}

// This is the sorting method. it takes in two arrays of 64 bit signed integers, one is the
// unsorted original array and one is the array for the output. It also takes in a 32 bit
// unsigned integer indicating the size of the arrays, both arrays are assumed as having
// size equal to the integer size. This function will takes in the unsorted array and copy
// the terms into the output array in sorted order from the lowest to highest.
static void CopyAndSort(int64_t in[], int64_t out[], uint32_t size) {
  // error case occurs when any array is null.
  if ((in == NULL) | (out == NULL)) {
    printf("invalid array\n");
  } else {
    for (uint32_t i = 0; i < size; i++) {
      out[i] = in[i];
      switcher(out, i);
    }
  }
}

// This is the recursive method for sorting function. It compares one term with the term before
// it (it does not do anything when dealing with the first element in the array), if the previous
// one is larger, it switches the previous one with the element right now and recurse on position
// before the position now. It takes in an integer array and an integer indicating current index
// as parameters.
static void switcher(int64_t ar[], uint32_t position) {
  if (position > 0) {
    int64_t now = ar[position];
    int64_t last = ar[position - 1];
    if (now < last) {
      ar[position] = last;
      ar[position - 1] = now;
      switcher(ar, position - 1);
    }
  }
}

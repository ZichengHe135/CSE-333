// Zicheng He 1534763 zicheh@uw.edu
// Copyright ©2018 Zicheng He.  All rights reserved.
// This is a script used for testing if the vector header works properly.
#include "Vector.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define SIZE 10  // Test vector length.
#define INIT 4  // Intitial vector length.

// Print the elements in the vector on a line.
static void PrintIntVector(vector_t v);

int main(int argc, char *argv[]) {
  uint32_t i;
  // create a new vector and check if malloc failed
  vector_t v = VectorCreate(INIT);
  if (v == NULL)
    return EXIT_FAILURE;

  for (i = 0; i < SIZE; i++) {
    // Place some elements in the vector.
    int *x = (int*)malloc(sizeof(int));
    if (x == NULL)
      return EXIT_FAILURE;
    *x = i;
    element_t old;
    bool success = VectorSet(v, i, x, &old);
    if (!success)
      return EXIT_FAILURE;
  }

  PrintIntVector(v);

  // free the heap usage
  for (i = 0; i < SIZE; i++) {
    element_t now = VectorGet(v, i);
    free(now);
  }
  VectorFree(v);

  return EXIT_SUCCESS;
}

static void PrintIntVector(vector_t v) {
  uint32_t i;
  size_t length;

  assert(v != NULL);

  length = VectorLength(v);

  if (length > 0) {
    printf("[%d", *((int*)VectorGet(v, 0)));
    for (i = 1; i < VectorLength(v); ++i)
      printf(",%d", *((int*)VectorGet(v, i)));
    printf("]\n");
  }
}

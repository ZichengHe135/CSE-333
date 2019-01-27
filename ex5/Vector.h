// Zicheng He 1534763 zicheh@uw.edu
// Copyright ©2018 Zicheng He.  All rights reserved.
#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

// An arbitrary pointer to represent an element in the vector.
typedef void* element_t;

// An expandable array of element_ts.
typedef struct vector_t {
  size_t length;
  element_t *arry;
} *vector_t;

// This function creates a new vector object with length of n,
// the new vector contains a array of length n with all NULL
// elemetns. When the function fails to allocate, return NULL.
vector_t VectorCreate(size_t n);

// Frees the memory allocated for the vector_t.  Assumes v != NULL.
void VectorFree(vector_t v);

// Sets the nth element of v to be e. Returns the previous nth element_t
// in prev. Freeing e is the responsibility of the user, not the
// vector_t. Returns true iff successful.  Assumes v != NULL.
// If the index if larger than the array length, we also will resize the
// array to be that long.
bool VectorSet(vector_t v, uint32_t index, element_t e, element_t *prev);

// Returns the element at the given index within v.  Assumes v != NULL.
element_t VectorGet(vector_t v, uint32_t index);

// Returns the length of v.  Assumes v != NULL.
size_t VectorLength(vector_t v);

#endif

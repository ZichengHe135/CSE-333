// Zicheng He 1534763 zicheh@uw.edu
// Copyright ©2018 Zicheng He.  All rights reserved.
// This script contains a struct that represent a point in 3 dimesion
// and a function to allocate a pointer for such a struct in the heap,
// the main function in this script is used for testing if both the
// struct and allocating method can work normally.
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

// This struct indicates a point's position in 3 dimesion. It stores the
// coordinate of x, y and z for the point as three 16 bit integers.
typedef struct Point3d {
  int16_t x;
  int16_t y;
  int16_t z;
} Point3d, *Point3dPtr;

Point3dPtr AllocatePoint3d(int16_t x, int16_t y, int16_t z);

int main(int argc, char **argv) {
  int16_t x = 1;
  int16_t y = 7;
  int16_t z = 3;

  Point3dPtr answer = AllocatePoint3d(x, y, z);
  if (answer == NULL) {
    printf("Error: malloc failed\n");
  }
  if ((answer->x != x) || (answer->y != y) || (answer->z != z)) {
    printf("Error: wrong value assigned\n");
    free(answer);
    return EXIT_FAILURE;
  } else {
    printf("test passed!\n");
    free(answer);
    return EXIT_SUCCESS;
  }
}

// This method allocates memory for a Point3d struct in the heap. It takes
// in three 16 bit integers as parameters and return a pointer of the
// Point3d struct allocated in the heap. Remember: This function use
// malloc to allocate space in heap, so be sure to free the block after
// using the Point3d object.
Point3dPtr AllocatePoint3d(int16_t x, int16_t y, int16_t z) {
  Point3dPtr result = (Point3dPtr) malloc(sizeof(Point3d));
  if (result != NULL) {
    result->x = x;
    result->y = y;
    result->z = z;
  }
  return result;
}

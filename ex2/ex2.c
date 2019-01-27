// Zicheng He 1534763 zicheh@uw.edu
// Copyright ©2018 Zicheng He.  All rights reserved.
// This script contains a function that can print out the contents of
// parameters of different data types in each byte. The function takes
// in a point of any types and a integer indicating the size of
// corresponding data type. The function will access and print out
// the address of the pointer and then print the contents pointed in
// each byte.
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>

static void DumpHex(void* pData, int byteLen);

int main(int argc, char **argv) {
  char     charVal = '0';
  int32_t  intVal = 1;
  float    floatVal = 1.0;
  double   doubleVal  = 1.0;

  typedef struct {
    char     charVal;
    int32_t  intVal;
    float    floatVal;
    double   doubleVal;
  } Ex2Struct;
  Ex2Struct structVal = { '0', 1, 1.0, 1.0 };

  DumpHex(&charVal, sizeof(char));
  DumpHex(&intVal, sizeof(int32_t));
  DumpHex(&floatVal, sizeof(float));
  DumpHex(&doubleVal, sizeof(double));
  DumpHex(&structVal, sizeof(structVal));

  return EXIT_SUCCESS;
}

// This function is used for accessing and printing the address of the
// pointer and contents pointed by that pointer. The parameter it takes
// in is a void pointer and a integer that indicates the length of the
// data type we want.
static void DumpHex(void* pData, int byteLen) {
  // first print out the address of the pointer
  printf("The %d bytes starting at %p are:", byteLen, pData);
  // print out values of the data by bytes, which can be comprehended as
  // unsigned 8 bits integer
  for (int i = 0; i < byteLen; i++) {
    uint8_t a_byte = *(uint8_t*) (pData + i);
    printf(" %02" PRIx8 "", a_byte);
  }
  printf("\n");
}


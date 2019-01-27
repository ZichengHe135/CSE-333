// Zicheng He 1534763 zicheh@uw.edu
// Copyright ©2018 Zicheng He.  All rights reserved.
// This script can read a file and print out the contents in the file
// in a reverse order, the file must exist and be non-empty and passed
// as an input argument.
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


int main(int argc, char *argv[]) {
  // check if correct number of arguments are passed in
  if (argc != 2) {
    fprintf(stderr, "Error: wrong number of inputs\n");
    return EXIT_FAILURE;
  }

  FILE *file = fopen(argv[1], "rb");
  // check if the input file exists
  if (file == NULL) {
    fprintf(stderr, "Error: input file does not exist\n");
    return EXIT_FAILURE;
  }

  // check if the file is empty or has no EOF, if the file is non-empty,
  // remember the size
  if (fseek(file, 0, SEEK_END) != 0) {
    fprintf(stderr, "Error: can't find end of the file\n");
    return EXIT_SUCCESS;
  }
  int64_t size = ftell(file);
  if (size <= 0) {
    fprintf(stderr, "Error: input file is empty\n");
    return EXIT_FAILURE;
  }

  // loop thorugh the file
  for (int64_t i = size - 1; i >= 0; i--) {
    // check if setting cursor fails
    if (fseek(file, i, SEEK_SET) != 0) {
      fprintf(stderr, "Error: can't set cursor\n");
    }
    char storage;
    // read one byte, which is the size of a char
    fread((void*) &storage, 1, 1, file);
    printf("%c", storage);
  }

  fclose(file);
  return EXIT_SUCCESS;
}

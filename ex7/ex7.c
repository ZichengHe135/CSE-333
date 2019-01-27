// Zicheng He 1534763 zicheh@uw.edu
// Copyright ©2018 Zicheng He.  All rights reserved.
// This script uses POSIX functions to read files and print them out to
// stdout. The script takes in a directory name as an argument, and will
// print out all the files that end with ".txt" in that directory
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define SIZE 1024

// Report Usage and exit
void Usage(void) {
  fprintf(stderr, "Usage: ex7 did not corectly execute\n");
  exit(EXIT_FAILURE);
}

// Print out a file's content, this function use POSIX functions to read
// and write file, it takes in a complete file name (with its path) as
// a parameter.
// Credit to CSE 333 TA: This function is taken from CSE 333 Section 3,
// filedump.c with some small modifications.
void Print(char* filename) {
  // open file
  int fd = open(filename, O_RDONLY);
  if (fd == -1) {
    Usage();
  }

  // create a buffer to store contents
  char buf[SIZE];
  ssize_t len;

  // loop though a file
  do {
    len = read(fd, buf, SIZE);
    if (len == -1) {
      if (errno != EINTR) {
        close(fd);
        Usage();
      }
      continue;
    }

    size_t total = 0;
    ssize_t wlen;
    while (total < len) {
      wlen = write(1, buf + total, len - total);
      if (wlen == -1) {
        if (errno != EINTR) {
          close(fd);
          Usage();
        }
        continue;
      }
      total += wlen;
    }
  } while (len > 0);

  // close the stream
  close(fd);
}

int main(int argc, char** argv) {
  // check for correct input
  if (argc != 2) {
    Usage();
  }

  // check for valid directory
  DIR* d = opendir(argv[1]);
  if (d == NULL) {
    Usage();
  }

  // loop through
  struct dirent *entry;
  entry = readdir(d);
  while (entry) {
    // find file name, execute only if it ends in .txt
    char* fname = entry->d_name;
    int name_len = strlen(fname);
    if ((name_len > 4) && (strcmp(fname + (name_len - 4), ".txt") == 0)) {
      // get the full path for this file
      int dlen = strlen(argv[1]);
      int flen = strlen(fname);
      char* fullname = (char *) malloc(sizeof(char) * (dlen + flen + 2));
      if (fullname == NULL) {
        Usage();
      }
      snprintf(fullname, dlen + flen + 2, "%s/%s", argv[1], fname);

      // print the content
      Print(fullname);

      free(fullname);
    }

    // to the next one
    entry = readdir(d);
  }

  // Clean up and exit
  closedir(d);
  return EXIT_SUCCESS;
}

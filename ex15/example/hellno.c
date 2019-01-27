#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define SIZE 1024

void Usage(void) {
  fprintf(stderr, "usage: ex7 directory\n");
  exit(EXIT_FAILURE);
}

void Print(char* filename) {
  int fd = open(filename, O_RDONLY);
  if (fd == -1) {
    Usage();
  }

  char buf[SIZE];
  ssize_t len;

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
    // find file name
    int name_len = strlen(entry->d_name);
    if ((name_len > 4) && (strcmp(entry->d_name + (name_len - 4), ".txt") == 0)) {

      int dlen = strlen(argv[1]);
      int flen = strlen(entry->d_name);
      char* fullname = (char *) malloc(sizeof(char) * (dlen + flen + 2));
      if (fullname == NULL) {
        Usage();
      }
      snprintf(fullname, dlen + flen + 2, "%s/%s", argv[1], entry->d_name);

      Print(fullname);
      free(fullname);
    }

    entry = readdir(d);
  }

  // Clean up and exit
  closedir(d);
  return EXIT_SUCCESS;
}

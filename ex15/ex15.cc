// Zicheng He 1534763 zicheh@uw.edu
// Copyright ©2018 Zicheng He.  All rights reserved.
// This script is used for connecting to a socket on an IP address and
// write out the contents of a target file to receiver on that server
#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <fcntl.h>
#include <iostream>

#include "./connect.h"

#define BUF 512

void Usage(char *progname);

int main(int argc, char **argv) {
  if (argc != 4) {
    Usage(argv[0]);
  }

  unsigned short port = 0;
  if (sscanf(argv[2], "%hu", &port) != 1) {
    Usage(argv[0]);
  }

  // Get an appropriate sockaddr structure.
  struct sockaddr_storage addr;
  size_t addrlen;
  if (!LookupName(argv[1], port, &addr, &addrlen)) {
    Usage(argv[0]);
  }

  // Connect to the remote host.
  int socket_fd;
  if (!Connect(addr, addrlen, &socket_fd)) {
    Usage(argv[0]);
  }

  // to read from file, open file first
  int file_fd = open(argv[3], O_RDONLY);
  if (file_fd == -1) {
    Usage(argv[0]);
  }

  // Read something from file
  // Will only read BUF-1 characters at most.
  char readbuf[BUF];
  int res;
  while (1) {
    res = read(file_fd, readbuf, BUF - 1);
    if (res == 0) {  // file ended
      break;
    }
    if (res == -1) {  // error
      if (errno == EINTR)
        continue;
      std::cerr << "file read failure: " << strerror(errno) << std::endl;
      close(socket_fd);
      close(file_fd);
      return EXIT_FAILURE;
    } else {
      readbuf[res] = '\0';
      std::cout << readbuf;
      // write out what is in the buffer to socket
      int wres = write(socket_fd, readbuf, res);
      if (wres == 0) {
        std::cerr << "socket closed prematurely" << std::endl;
        close(socket_fd);
        close(file_fd);
        return EXIT_FAILURE;
      }
      if (wres == -1) {
        if (errno == EINTR)
          continue;
        std::cerr << "socket write failure: " << strerror(errno) << std::endl;
        close(socket_fd);
        close(file_fd);
        return EXIT_FAILURE;
      }
    }
  }
  // Clean up.
  close(socket_fd);
  close(file_fd);
  return EXIT_SUCCESS;
}

void Usage(char *progname) {
  std::cerr << "usage: " << progname << " hostname port" << std::endl;
  exit(EXIT_FAILURE);
}



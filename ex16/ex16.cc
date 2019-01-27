// Zicheng He 1534763 zicheh@uw.edu
// Copyright ©2018 Zicheng He.  All rights reserved.
// This script can be used for server side file transferring, most of the
// code are taken from CSE 333 course website under lecture 23, with my
// modification
#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>

#include "./Listen.h"

void Usage(char *progname);

int main(int argc, char **argv) {
  // Expect the port number as a command line argument.
  if (argc != 2) {
    Usage(argv[0]);
  }

  int sock_family;
  int listen_fd = Listen(argv[1], &sock_family);
  if (listen_fd <= 0) {
    // We failed to bind/listen to a socket.  Quit with failure.
    std::cerr << "Couldn't bind to any addresses." << std::endl;
    return EXIT_FAILURE;
  }

  // Loop forever, accepting a connection from a client and doing
  // an echo trick to it.
  while (1) {
    struct sockaddr_storage caddr;
    socklen_t caddr_len = sizeof(caddr);
    int client_fd = accept(listen_fd,
                           reinterpret_cast<struct sockaddr *>(&caddr),
                           &caddr_len);
    if (client_fd < 0) {
      if ((errno == EINTR) || (errno == EAGAIN) || (errno == EWOULDBLOCK))
        continue;
      std::cerr << "Failure on accept: " << strerror(errno) << std::endl;
      break;
    }

    HandleClient(client_fd,
                 reinterpret_cast<struct sockaddr *>(&caddr),
                 caddr_len,
                 sock_family);
    break;
  }

  // Close up shop.
  close(listen_fd);
  return EXIT_SUCCESS;
}

void Usage(char *progname) {
  std::cerr << "usage: " << progname << " port" << std::endl;
  exit(EXIT_FAILURE);
}



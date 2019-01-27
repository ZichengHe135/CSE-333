// Zicheng He 1534763 zicheh@uw.edu
// Copyright ©2018 Zicheng He.  All rights reserved.
// This is a header file for methods used for server side connection
#ifndef _LISTEN_H_
#define _LISTEN_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>

int  Listen(char *portnum, int *sock_family);
void HandleClient(int c_fd, struct sockaddr *addr, size_t addrlen,
                  int sock_family);

#endif  // _LISTEN_H_

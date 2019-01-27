// Zicheng He 1534763 zicheh@uw.edu
// Copyright ©2018 Zicheng He.  All rights reserved.
// This is a header file for methods that are used to connect to a socket
// on an IP address, the code is taken from CSE333 course website under
// lecture 22
#ifndef _CONNECT_H_
#define _CONNECT_H_

#include <sys/socket.h>
#include <sys/types.h>

bool LookupName(char *name,
                unsigned short port,
                struct sockaddr_storage *ret_addr,
                size_t *ret_addrlen);

bool Connect(const struct sockaddr_storage &addr,
             const size_t &addrlen,
             int *ret_fd);

#endif  // _CONNECT_H_

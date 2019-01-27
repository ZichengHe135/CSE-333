/*
 * Copyright ©2018 Hal Perkins.  All rights reserved.  Permission is
 * hereby granted to students registered for University of Washington
 * CSE 333 for use solely during Summer Quarter 2018 for purposes of
 * the course.  No other use, copying, distribution, or modification
 * is permitted without prior written consent. Copyrights for
 * third-party components of this work must be honored.  Instructors
 * interested in reusing these course materials should contact the
 * author.
 */

#include <stdio.h>       // for snprintf()
#include <unistd.h>      // for close(), fcntl()
#include <sys/types.h>   // for socket(), getaddrinfo(), etc.
#include <sys/socket.h>  // for socket(), getaddrinfo(), etc.
#include <arpa/inet.h>   // for inet_ntop()
#include <netdb.h>       // for getaddrinfo()
#include <errno.h>       // for errno, used by strerror()
#include <string.h>      // for memset, strerror()
#include <iostream>      // for std::cerr, etc.

#include "./ServerSocket.h"

extern "C" {
  #include "libhw1/CSE333.h"
}

namespace hw4 {

ServerSocket::ServerSocket(uint16_t port) {
  port_ = port;
  listen_sock_fd_ = -1;
}

ServerSocket::~ServerSocket() {
  // Close the listening socket if it's not zero.  The rest of this
  // class will make sure to zero out the socket if it is closed
  // elsewhere.
  if (listen_sock_fd_ != -1)
    close(listen_sock_fd_);
  listen_sock_fd_ = -1;
}

bool ServerSocket::BindAndListen(int ai_family, int *listen_fd) {
  // Use "getaddrinfo," "socket," "bind," and "listen" to
  // create a listening socket on port port_.  Return the
  // listening socket through the output parameter "listen_fd".

  // MISSING:
  if (ai_family != AF_INET && ai_family != AF_INET6 && ai_family != AF_UNSPEC)
    return false;

  struct addrinfo ai;
  memset(&ai, 0, sizeof(ai));

  ai.ai_family = ai_family;
  ai.ai_socktype = SOCK_STREAM;
  ai.ai_flags = AI_PASSIVE;
  ai.ai_protocol = IPPROTO_TCP;
  ai.ai_canonname = NULL;
  ai.ai_addr = NULL;
  ai.ai_next = NULL;

  std::string port = std::to_string(port_);
  struct addrinfo *result;
  int res = getaddrinfo(NULL, port.c_str(), &ai, &result);
  if (res != 0) {  // failed
    return false;
  }

  struct addrinfo* now = result;
  bool found = false;
  int sock_fd;
  while (now != NULL) {
    // create socket
    sock_fd = socket(now->ai_family,
                     now->ai_socktype,
                     now->ai_protocol);
    if (sock_fd == -1) {  // failed, go to next
      now = now->ai_next;
      continue;
    }

    // configure the socket
    int optval = 1;
    res = setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR,
                     &optval, sizeof(optval));
    if (res != 0) {  // failed, go to next
      close(sock_fd);
      now = now->ai_next;
      continue;
    }

    // bind the socket
    res = bind(sock_fd, now->ai_addr, now->ai_addrlen);
    if (res != 0) {  // failed
      close(sock_fd);
    } else {  // success
      sock_family_ = now->ai_family;
      found = true;
      break;
    }
    now = now->ai_next;
  }

  freeaddrinfo(result);

  if (found) {  // success
    res = listen(sock_fd, SOMAXCONN);
    if (res != 0) {  // listen failed
      close(sock_fd);
      return false;
    }
    listen_sock_fd_ = sock_fd;
    *listen_fd = sock_fd;
    return true;
  } else {
    return false;
  }
}

bool ServerSocket::Accept(int *accepted_fd,
                          std::string *client_addr,
                          uint16_t *client_port,
                          std::string *client_dnsname,
                          std::string *server_addr,
                          std::string *server_dnsname) {
  // Accept a new connection on the listening socket listen_sock_fd_.
  // (Block until a new connection arrives.)  Return the newly accepted
  // socket, as well as information about both ends of the new connection,
  // through the various output parameters.

  // MISSING:
  int res;
  int client_fd;
  struct sockaddr* addr;
  struct sockaddr_storage caddr;
  socklen_t caddr_len = sizeof(caddr);
  while (1) {
    addr = reinterpret_cast<struct sockaddr *>(&caddr);
    client_fd = accept(listen_sock_fd_, addr, &caddr_len);
    if (client_fd < 0) {
      if ((errno == EAGAIN) || (errno == EINTR))
        continue;  // keep trying
      return false;
    }
    break;  // accept successed, stop trying
  }

  *accepted_fd = client_fd;
  if (addr->sa_family == AF_INET) {
    char astring[INET_ADDRSTRLEN];
    struct sockaddr_in *v4addr = (struct sockaddr_in *) addr;
    inet_ntop(AF_INET, &(v4addr->sin_addr), astring, INET_ADDRSTRLEN);
    *client_addr = std::string(astring);
    *client_port = htons(v4addr->sin_port);
  } else if (addr->sa_family == AF_INET6) {
    char astring[INET6_ADDRSTRLEN];
    struct sockaddr_in6 *v6addr = (struct sockaddr_in6 *) addr;
    inet_ntop(AF_INET6, &(v6addr->sin6_addr), astring, INET6_ADDRSTRLEN);
    *client_addr = std::string(astring);
    *client_port = htons(v6addr->sin6_port);
  } else {
    return false;
  }

  char hostname[1024];
  res = getnameinfo(addr, caddr_len, hostname, 1024, NULL, 0, 0);
  if (res != 0) {
    return false;
  } else {
    *client_dnsname = std::string(hostname);
  }

  char hname[1024];
  hname[0] = '\0';
  if (sock_family_ == AF_INET) {
    struct sockaddr_in s_v4;
    socklen_t s_v4_len = sizeof(s_v4);
    char addrbuf[INET_ADDRSTRLEN];
    getsockname(client_fd, (struct sockaddr*)&s_v4, &s_v4_len);
    inet_ntop(AF_INET, &s_v4.sin_addr, addrbuf, INET_ADDRSTRLEN);
    getnameinfo((struct sockaddr*)&s_v4, s_v4_len, hname,
                1024, NULL, 0, 0);
    *server_addr = addrbuf;
    *server_dnsname = hname;
  } else if (sock_family_ == AF_INET6) {
    struct sockaddr_in s_v6;
    socklen_t s_v6_len = sizeof(s_v6);
    char addrbuf[INET6_ADDRSTRLEN];
    getsockname(client_fd, (struct sockaddr*)&s_v6, &s_v6_len);
    inet_ntop(AF_INET6, &s_v6.sin_addr, addrbuf, INET6_ADDRSTRLEN);
    getnameinfo((struct sockaddr*)&s_v6, s_v6_len, hname,
                1024, NULL, 0, 0);
    *server_addr = addrbuf;
    *server_dnsname = hname;
  } else {
    return false;
  }

  return true;
}

}  // namespace hw4

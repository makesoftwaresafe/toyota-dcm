/* Copyright 2022 ForAllSecure, Inc (https://forallsecure.com).  Code
 * contributed to be licensed under the same license as the original code.  */

#include <dlfcn.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <sys/socket.h>

#include <cassert>
#include <cstdarg>
#include <cstring>
#include <iostream>
#include <memory>
#include <unordered_map>

#include "State.h"
#include "UntrackedState.h"

/**
 * A table of socket file descriptors to their current state in the harness.
 */
static std::unordered_map<int, std::shared_ptr<State>> harness_state = {};

extern "C" {

static int (*real_close)(int) = NULL;

int close(int fd) {
  if (NULL == real_close) {
    real_close =
        reinterpret_cast<typeof(real_close)>(dlsym(RTLD_NEXT, "close"));
    assert(real_close);
  }

  int res = real_close(fd);
  if (-1 != res) {
    harness_state.erase(fd);
  }
  return res;
}

static int (*real_socket)(int domain, int type, int protocol) = NULL;

int socket(int domain, int type, int protocol) {
  // if the real socket call hasn't been initialized, do it now.
  if (NULL == real_socket) {
    real_socket =
        reinterpret_cast<typeof(real_socket)>(dlsym(RTLD_NEXT, "socket"));
    assert(real_socket);
  }

  // First call the system's "socket" call.
  int fd = real_socket(domain, type, protocol);
  if (-1 != fd) {
    // If successful, construct a SocketCreatedState object and place it into
    // the table.
    assert(
        harness_state.emplace(fd, std::make_shared<UntrackedState>(fd)).second);
  }

  return fd;
}

int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
  int res = -1;
  harness_state.at(sockfd) = harness_state.at(sockfd)->bind(res, addr, addrlen);
  return res;
}

ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags) {
  ssize_t res = -1;
  harness_state.at(sockfd) = harness_state.at(sockfd)->recvmsg(res, msg, flags);
  return res;
}

ssize_t sendto(int socket, const void *message, size_t length, int flags,
               const struct sockaddr *dest_addr, socklen_t dest_len) {
  ssize_t res = -1;
  harness_state.at(socket) = harness_state.at(socket)->sendto(
      res, message, length, flags, dest_addr, dest_len);
  return res;
}

int setsockopt(int socket, int level, int option_name, const void *option_value,
               socklen_t option_len) {
  return harness_state.at(socket)->setsockopt(socket, level, option_name,
                                              option_value, option_len);
}

int getsockname(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
  return harness_state.at(sockfd)->getsockname(sockfd, addr, addrlen);
}

int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
           struct timeval *timeout) {
  int res = 0;
  for (int fd = 0; fd < nfds; fd++) {
    // only handle reading for now
    FD_CLR(fd, writefds);
    FD_CLR(fd, exceptfds);
    if (FD_ISSET(fd, readfds)) {
      auto find_result = harness_state.find(fd);
      if (harness_state.end() == find_result ||
          !find_result->second->data_available()) {
        FD_CLR(fd, readfds);
      } else {
        res++;
      }
    }
  }
  return res;
}

/**
 * Handles SIOCGIF* calls.
 */
int ioctl(int fd, unsigned long request, ...) {
  va_list args;
  struct ifreq *rq = NULL;

  va_start(args, request);
  rq = va_arg(args, struct ifreq *);

  if (SIOCGIFNAME == request) {
    /* fill in ifr_name with "eth0" */
    strncpy(rq->ifr_name, "eth0", IFNAMSIZ);

    /* return indicating success */
    return 0;
  } else if (SIOCGIFFLAGS == request) {
    /* zero out flags */
    rq->ifr_flags = 0;

    /* return indicating success */
    return 0;
  } else if (SIOCGIFMTU == request) {
    rq->ifr_mtu = 1500; /* usually 1500 is right */
    return 0;
  }
  abort();
}
}

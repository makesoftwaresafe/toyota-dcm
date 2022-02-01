/* Copyright 2022 ForAllSecure, Inc (https://forallsecure.com).  Code
 * contributed to be licensed under the same license as the original code.  */

#include "UntrackedState.h"

#include <dlfcn.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <cassert>
#include <iostream>

#include "FakeNetlinkReadyState.h"
#include "FuzzPayloadReadyState.h"

static int (*real_bind)(int, const struct sockaddr *, socklen_t) = NULL;
static ssize_t (*real_recvmsg)(int, struct msghdr *, int) = NULL;
static ssize_t (*real_sendto)(int, const void *pVoid, size_t size, int i,
                              const struct sockaddr *sockaddr,
                              socklen_t socklen) = NULL;
static int (*real_setsockopt)(int socket, int level, int option_name,
                              const void *option_value,
                              socklen_t option_len) = NULL;
static int (*real_getsockname)(int sockfd, struct sockaddr *addr,
                               socklen_t *addrlen) = NULL;

UntrackedState::UntrackedState(int fd) : fd(fd) {}

std::shared_ptr<State> UntrackedState::bind(int &result,
                                            const struct sockaddr *sockaddr,
                                            socklen_t socklen) {
  if (NULL == real_bind) {
    real_bind = reinterpret_cast<typeof(real_bind)>(dlsym(RTLD_NEXT, "bind"));
    assert(real_bind);
  }
  std::shared_ptr<State> new_state;

  std::cerr << "UntrackedState -> ";
  if (AF_NETLINK == sockaddr->sa_family) {
    // Case 1. address is netlink, return netlink ready state.
    result = 0;
    new_state = std::make_shared<FakeNetlinkReadyState>();
    std::cerr << "FakeNetlinkReadyState\n";
  } else if (AF_INET6 == sockaddr->sa_family &&
             547 == htons(((struct sockaddr_in6 *)sockaddr)->sin6_port)) {
    // Case 2. address is the port we're fuzzing
    result = 0;
    new_state = std::make_shared<FuzzPayloadReadyState>();
    std::cerr << "FuzzPayloadReadyState\n";
  } else {
    // Case 3. No match, fallback to regular bind.
    result = real_bind(fd, sockaddr, socklen);
    new_state = shared_from_this();
    std::cerr << "UntrackedState\n";
    // abort(); /* TODO: I think this case shouldn't even be handled. */
  }
  return new_state;
}

std::shared_ptr<State> UntrackedState::recvmsg(ssize_t &ssize,
                                               struct msghdr *msghdr,
                                               int flags) {
  if (NULL == real_recvmsg) {
    real_recvmsg =
        reinterpret_cast<typeof(real_recvmsg)>(dlsym(RTLD_NEXT, "recvmsg"));
    assert(real_recvmsg);
  }
  ssize = real_recvmsg(fd, msghdr, flags);
  return shared_from_this();
}

std::shared_ptr<State> UntrackedState::sendto(ssize_t &ssize,
                                              const void *message,
                                              size_t length, int flags,
                                              const struct sockaddr *sockaddr,
                                              socklen_t socklen) {
  if (NULL == real_sendto) {
    real_sendto =
        reinterpret_cast<typeof(real_sendto)>(dlsym(RTLD_NEXT, "sendto"));
    assert(real_sendto);
  }
  ssize = real_sendto(fd, message, length, flags, sockaddr, socklen);
  return shared_from_this();
}

int UntrackedState::setsockopt(int socket, int level, int option_name,
                               const void *option_value, socklen_t option_len) {
  if (NULL == real_setsockopt) {
    real_setsockopt = reinterpret_cast<typeof(real_setsockopt)>(
        dlsym(RTLD_NEXT, "setsockopt"));
    assert(real_setsockopt);
  }
  return real_setsockopt(socket, level, option_name, option_value, option_len);
}

int UntrackedState::getsockname(int sockfd, struct sockaddr *addr,
                                socklen_t *addrlen) {
  throw std::runtime_error("Unexpected getsockname");
}

bool UntrackedState::data_available() const {
  throw std::runtime_error("Unexpected data available call");
}

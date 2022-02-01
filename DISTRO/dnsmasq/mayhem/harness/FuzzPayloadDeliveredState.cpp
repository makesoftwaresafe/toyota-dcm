/* Copyright 2022 ForAllSecure, Inc (https://forallsecure.com).  Code
 * contributed to be licensed under the same license as the original code.  */

#include "FuzzPayloadDeliveredState.h"

#include <iostream>

std::shared_ptr<State> FuzzPayloadDeliveredState::bind(
    int &i, const struct sockaddr *sockaddr, socklen_t socklen) {
  throw std::runtime_error("Unexpected bind");
}

std::shared_ptr<State> FuzzPayloadDeliveredState::recvmsg(ssize_t &ssize,
                                                          struct msghdr *msghdr,
                                                          int i) {
  throw std::runtime_error("Payload already delivered");
}

std::shared_ptr<State> FuzzPayloadDeliveredState::sendto(
    ssize_t &ssize, const void *pVoid, size_t size, int i,
    const struct sockaddr *sockaddr, socklen_t socklen) {
  ssize = size;
  return shared_from_this();
}

int FuzzPayloadDeliveredState::setsockopt(int socket, int level,
                                          int option_name,
                                          const void *option_value,
                                          socklen_t option_len) {
  throw std::runtime_error("Unexpected setsockopt");
}

int FuzzPayloadDeliveredState::getsockname(int sockfd, struct sockaddr *addr,
                                           socklen_t *addrlen) {
  throw std::runtime_error("Unexpected getsockname");
}

bool FuzzPayloadDeliveredState::data_available() const {
  std::cerr << "Goodbye!";
  std::exit(0);
}

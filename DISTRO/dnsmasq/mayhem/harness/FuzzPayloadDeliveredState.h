/* Copyright 2022 ForAllSecure, Inc (https://forallsecure.com).  Code
 * contributed to be licensed under the same license as the original code.  */

#ifndef DNSMASQ_HARNESS_FUZZPAYLOADDELIVEREDSTATE_H
#define DNSMASQ_HARNESS_FUZZPAYLOADDELIVEREDSTATE_H

#include "State.h"

class FuzzPayloadDeliveredState
    : public State,
      public std::enable_shared_from_this<FuzzPayloadDeliveredState> {
 public:
  std::shared_ptr<State> bind(int &i, const struct sockaddr *sockaddr,
                              socklen_t socklen) override;

  std::shared_ptr<State> recvmsg(ssize_t &ssize, struct msghdr *msghdr,
                                 int i) override;

  std::shared_ptr<State> sendto(ssize_t &ssize, const void *pVoid, size_t size,
                                int i, const struct sockaddr *sockaddr,
                                socklen_t socklen) override;

  int setsockopt(int socket, int level, int option_name,
                 const void *option_value, socklen_t option_len) override;

  int getsockname(int sockfd, struct sockaddr *addr,
                  socklen_t *addrlen) override;

  bool data_available() const override;
};

#endif  // DNSMASQ_HARNESS_FUZZPAYLOADDELIVEREDSTATE_H

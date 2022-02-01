/* Copyright 2022 ForAllSecure, Inc (https://forallsecure.com).  Code
 * contributed to be licensed under the same license as the original code.  */

#ifndef DNSMASQ_HARNESS_STATE_H
#define DNSMASQ_HARNESS_STATE_H

#include <sys/socket.h>

#include <memory>

class State {
 public:
  // state transition methods
  virtual std::shared_ptr<State> bind(int &, const struct sockaddr *,
                                      socklen_t) = 0;
  virtual std::shared_ptr<State> recvmsg(ssize_t &, struct msghdr *, int) = 0;
  virtual std::shared_ptr<State> sendto(ssize_t &, const void *, size_t, int,
                                        const struct sockaddr *, socklen_t) = 0;

  // non-transition methods
  virtual int setsockopt(int socket, int level, int option_name,
                         const void *option_value, socklen_t option_len) = 0;
  virtual int getsockname(int sockfd, struct sockaddr *addr,
                          socklen_t *addrlen) = 0;
  virtual bool data_available() const = 0;
};

#endif  // DNSMASQ_HARNESS_STATE_H

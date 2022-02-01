/* Copyright 2022 ForAllSecure, Inc (https://forallsecure.com).  Code
 * contributed to be licensed under the same license as the original code.  */

#include "FakeNetlinkDoneState.h"

#include <linux/netlink.h>

#include <iostream>

#include "FakeNetlinkReadyState.h"

FakeNetlinkDoneState::FakeNetlinkDoneState(uint32_t seq, uint32_t pid)
    : nl_seq(seq), nl_pid(pid) {}

std::shared_ptr<State> FakeNetlinkDoneState::bind(
    int &i, const struct sockaddr *sockaddr, socklen_t socklen) {
  throw std::runtime_error("Unexpected call to bind");
}

std::shared_ptr<State> FakeNetlinkDoneState::recvmsg(ssize_t &ssize,
                                                     struct msghdr *msg,
                                                     int flags) {
  struct sockaddr_nl *msg_name = static_cast<sockaddr_nl *>(msg->msg_name);
  msg_name->nl_family = AF_NETLINK;
  msg_name->nl_pid = nl_pid;

  struct iovec *iov = msg->msg_iov;
  struct nlmsghdr *nlh = static_cast<nlmsghdr *>(iov->iov_base);
  nlh = static_cast<struct nlmsghdr *>(iov->iov_base);
  nlh->nlmsg_seq = nl_seq;
  nlh->nlmsg_pid = 666;          /* TODO: don't hardcode */
  nlh->nlmsg_len = iov->iov_len; /* TBD */
  nlh->nlmsg_type = NLMSG_DONE;

  ssize = iov->iov_len;
  if (flags & MSG_PEEK) {
    std::cerr << "recvmsg: FakeNetlinkDoneState -> FakeNetlinkDoneState\n";
    return shared_from_this();
  } else {
    std::cerr << "recvmsg: FakeNetlinkDoneState -> FakeNetlinkReadyState\n";
    return std::make_shared<FakeNetlinkReadyState>();
  }
}

std::shared_ptr<State> FakeNetlinkDoneState::sendto(
    ssize_t &ssize, const void *pVoid, size_t size, int i,
    const struct sockaddr *sockaddr, socklen_t socklen) {
  throw std::runtime_error("Unexpected call to sendto");
}

int FakeNetlinkDoneState::setsockopt(int socket, int level, int option_name,
                                     const void *option_value,
                                     socklen_t option_len) {
  throw std::runtime_error("Unexpected setsockopt");
}

int FakeNetlinkDoneState::getsockname(int sockfd, struct sockaddr *addr,
                                      socklen_t *addrlen) {
  throw std::runtime_error("Unexpected getsockname");
}

bool FakeNetlinkDoneState::data_available() const {
  throw std::runtime_error("Unexpected data available check");
}

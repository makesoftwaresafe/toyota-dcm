/* Copyright 2022 ForAllSecure, Inc (https://forallsecure.com).  Code
 * contributed to be licensed under the same license as the original code.  */

#include "FakeNetlinkReadyState.h"

#include <linux/netlink.h>
#include <linux/rtnetlink.h>

#include <cassert>

#include "FakeNetlinkGetAddrState.h"

FakeNetlinkReadyState::FakeNetlinkReadyState() : netlink_pid(666) {}

std::shared_ptr<State> FakeNetlinkReadyState::bind(
    int &i, const struct sockaddr *sockaddr, socklen_t socklen) {
  throw std::runtime_error("bind - not yet implemented");
}

std::shared_ptr<State> FakeNetlinkReadyState::recvmsg(ssize_t &ssize,
                                                      struct msghdr *msghdr,
                                                      int i) {
  throw std::runtime_error("unexpected recvmsg");
}

std::shared_ptr<State> FakeNetlinkReadyState::sendto(
    ssize_t &ssize, const void *message, size_t length, int flags,
    const struct sockaddr *sockaddr, socklen_t socklen) {
  const struct nlmsghdr *nlh =
      reinterpret_cast<const struct nlmsghdr *>(message);
  assert(RTM_GETADDR ==
         nlh->nlmsg_type);  // only handle GETADDR requests right now
  ssize = length;
  return std::make_shared<FakeNetlinkGetAddrState>(nlh->nlmsg_seq,
                                                   nlh->nlmsg_pid);
}

int FakeNetlinkReadyState::setsockopt(int socket, int level, int option_name,
                                      const void *option_value,
                                      socklen_t option_len) {
  throw std::runtime_error("Unexpected setsockopt");
}

int FakeNetlinkReadyState::getsockname(int sockfd, struct sockaddr *addr,
                                       socklen_t *addrlen) {
  struct sockaddr_nl *nl_addr = reinterpret_cast<struct sockaddr_nl *>(addr);
  nl_addr->nl_family = AF_NETLINK;
  nl_addr->nl_pid = netlink_pid;
  *addrlen = sizeof(*nl_addr);
  return 0;
}

bool FakeNetlinkReadyState::data_available() const {
  return false;
  // throw std::runtime_error("Unexpected data available call");
}

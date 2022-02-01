/* Copyright 2022 ForAllSecure, Inc (https://forallsecure.com).  Code
 * contributed to be licensed under the same license as the original code.  */

#include "FakeNetlinkGetAddrState.h"

#include <arpa/inet.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>

#include <iostream>

#include "FakeNetlinkDoneState.h"

#define MAGIC_INTERFACE_VALUE 42

FakeNetlinkGetAddrState::FakeNetlinkGetAddrState(uint32_t seq, uint32_t pid)
    : nl_seq(seq), nl_pid(pid) {}

std::shared_ptr<State> FakeNetlinkGetAddrState::bind(
    int &i, const struct sockaddr *sockaddr, socklen_t socklen) {
  throw std::runtime_error("bind should not be called");
}

std::shared_ptr<State> FakeNetlinkGetAddrState::recvmsg(ssize_t &ssize,
                                                        struct msghdr *msg,
                                                        int flags) {
  struct sockaddr_nl *nl_name =
      static_cast<struct sockaddr_nl *>(msg->msg_name);
  nl_name->nl_pid = nl_pid;

  struct iovec *iov = msg->msg_iov;
  struct nlmsghdr *nlh = static_cast<nlmsghdr *>(iov->iov_base);
  nlh->nlmsg_seq = nl_seq;
  nlh->nlmsg_pid = 666;          /* TODO: make this not hardcoded */
  nlh->nlmsg_len = iov->iov_len; /* TBD */
  nlh->nlmsg_type = RTM_NEWADDR;

  struct ifaddrmsg *ifa = static_cast<ifaddrmsg *>(NLMSG_DATA(nlh));
  ifa->ifa_family = AF_INET6;
  ifa->ifa_index = MAGIC_INTERFACE_VALUE; /* refactor this part */
  ifa->ifa_scope = RT_SCOPE_SITE;
  ifa->ifa_prefixlen = 64;
  struct rtattr *rta = static_cast<rtattr *>(IFA_RTA(ifa));
  rta->rta_type = IFA_ADDRESS;
  rta->rta_len = sizeof(struct rtattr); /* TBD */
  struct in6_addr *addrp = (struct in6_addr *)(rta + 1);
  inet_pton(AF_INET6, "fec0::ffff:0:242:ac11:2", addrp);

  ssize = iov->iov_len;

  if (flags & MSG_PEEK) {
    std::cerr
        << "recvmsg: FakeNetlinkGetAddrState -> FakeNetlinkGetAddrState\n";
    return shared_from_this();
  } else {
    std::cerr << "recvmsg: FakeNetlinkGetAddrState -> FakeNetlinkDoneState\n";
    return std::make_shared<FakeNetlinkDoneState>(nl_seq, nl_pid);
  }
}

std::shared_ptr<State> FakeNetlinkGetAddrState::sendto(
    ssize_t &ssize, const void *pVoid, size_t size, int i,
    const struct sockaddr *sockaddr, socklen_t socklen) {
  throw std::runtime_error("sendto not supported during GetAddr");
}

int FakeNetlinkGetAddrState::setsockopt(int socket, int level, int option_name,
                                        const void *option_value,
                                        socklen_t option_len) {
  throw std::runtime_error("unexpected setsockopt");
}

int FakeNetlinkGetAddrState::getsockname(int sockfd, struct sockaddr *addr,
                                         socklen_t *addrlen) {
  throw std::runtime_error("unexpected getsockname");
}

bool FakeNetlinkGetAddrState::data_available() const {
  throw std::runtime_error("unexpected data available call");
}

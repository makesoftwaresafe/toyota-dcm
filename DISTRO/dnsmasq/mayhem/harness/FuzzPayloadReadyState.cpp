/* Copyright 2022 ForAllSecure, Inc (https://forallsecure.com).  Code
 * contributed to be licensed under the same license as the original code.  */

#include <netinet/in.h>
#include <sys/socket.h>
//#include <linux/in6.h>

#include "FuzzPayloadDeliveredState.h"
#include "FuzzPayloadReadyState.h"

std::shared_ptr<State> FuzzPayloadReadyState::bind(
    int &i, const struct sockaddr *sockaddr, socklen_t socklen) {
  throw std::runtime_error("Bind should not occur here!");
}

std::shared_ptr<State> FuzzPayloadReadyState::recvmsg(ssize_t &ssize,
                                                      struct msghdr *msghdr,
                                                      int flag) {
  // save the current offset into the file
  auto pos = payload_stream.tellg();

  // read the payload
  struct iovec *iov = msghdr->msg_iov;
  payload_stream.read(static_cast<char *>(iov->iov_base), iov->iov_len);
  ssize = payload_stream.gcount();

  // mark the message as truncated if the end of the payload was not reached
  if (!payload_stream.eof()) {
    msghdr->msg_flags |= MSG_TRUNC;
  }

  struct cmsghdr *cmsg = static_cast<struct cmsghdr *>(msghdr->msg_control);
  cmsg->cmsg_level = IPPROTO_IPV6;
  cmsg->cmsg_type = IPV6_PKTINFO;
  struct in6_pktinfo *pktinfo = (struct in6_pktinfo *)(cmsg + 1);
  /* set the interface index to a magic value to fake an interface */
  pktinfo->ipi6_ifindex = 42;

  if (flag & MSG_PEEK) {
    payload_stream.clear();
    payload_stream.seekg(pos);
    return shared_from_this();
  } else if (payload_stream.eof()) {
    return std::make_shared<FuzzPayloadDeliveredState>();
  }

  throw std::runtime_error("Unexpected error");
}

std::shared_ptr<State> FuzzPayloadReadyState::sendto(
    ssize_t &ssize, const void *pVoid, size_t size, int i,
    const struct sockaddr *sockaddr, socklen_t socklen) {
  throw std::runtime_error("sendto should not occur here");
}

int FuzzPayloadReadyState::setsockopt(int socket, int level, int option_name,
                                      const void *option_value,
                                      socklen_t option_len) {
  return 0;
  // throw std::runtime_error("Unexpected setsockopt");
}

int FuzzPayloadReadyState::getsockname(int sockfd, struct sockaddr *addr,
                                       socklen_t *addrlen) {
  throw std::runtime_error("Unexpected getsockname");
}

bool FuzzPayloadReadyState::data_available() const {
  return payload_stream.good();
}

FuzzPayloadReadyState::FuzzPayloadReadyState()
    : payload_stream("/tmp/fakenet_payload", std::ios::binary) {}

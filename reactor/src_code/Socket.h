

#ifndef xihoo_NET_SOCKET_H
#define xihoo_NET_SOCKET_H

#include <boost/noncopyable.hpp>

namespace xihoo
{

class InetAddress;


class Socket : boost::noncopyable
{
 public:
  explicit Socket(int sockfd)
    : sockfd_(sockfd)
  { }

  ~Socket();

  int fd() const { return sockfd_; }

  
  void bindAddress(const InetAddress& localaddr);
  
  void listen();

 
  int accept(InetAddress* peeraddr);

  

  void setReuseAddr(bool on);

  void shutdownWrite();


  void setTcpNoDelay(bool on);

 private:
  const int sockfd_;
};

}
#endif  

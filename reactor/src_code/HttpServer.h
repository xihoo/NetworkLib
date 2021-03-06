#ifndef xihoo_NET_HTTP_HTTPSERVER_H
#define xihoo_NET_HTTP_HTTPSERVER_H

#include "TcpServer.h"
#include <boost/noncopyable.hpp>
#include "HttpRequest.h"
#include "HttpResponse.h"

namespace xihoo
{
class HttpServer : boost::noncopyable
{
 public:
  typedef boost::function<void (const HttpRequest&,
                                HttpResponse*)> HttpCallback;

  HttpServer(EventLoop* loop,
             const InetAddress& listenAddr);

  ~HttpServer();  

  EventLoop* getLoop() const { return server_.getloop(); }

  
  void setHttpCallback(const HttpCallback& cb)
  {
    httpCallback_ = cb;
  }

  void setThreadNum(int numThreads)
  {
    server_.setThreadNum(numThreads);
  }

  void start();

 private:
  void onConnection(const TcpConnectionPtr& conn);
  void onMessage(const TcpConnectionPtr& conn,
                 Buffer* buf,
                 Timestamp receiveTime);
  void onRequest(const TcpConnectionPtr&, const HttpRequest&);

  TcpServer server_;
  HttpCallback httpCallback_;
};


}

#endif  

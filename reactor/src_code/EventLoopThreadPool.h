
#ifndef xihoo_NET_EVENTLOOPTHREADPOOL_H
#define xihoo_NET_EVENTLOOPTHREADPOOL_H

#include "thread/Condition.h"
#include "thread/Mutex.h"
#include "thread/Thread.h"


#include <vector>
#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

namespace xihoo
{

class EventLoop;
class EventLoopThread;

class EventLoopThreadPool : boost::noncopyable
{
 public:
  EventLoopThreadPool(EventLoop* baseLoop);
  ~EventLoopThreadPool();
  void setThreadNum(int numThreads) { numThreads_ = numThreads; }
  void start();
  EventLoop* getNextLoop();

 private:
  EventLoop* baseLoop_;
  bool started_;
  int numThreads_;
  int next_;  
  boost::ptr_vector<EventLoopThread> threads_;
  std::vector<EventLoop*> loops_;
};

}

#endif  

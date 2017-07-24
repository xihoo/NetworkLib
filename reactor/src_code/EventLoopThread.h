

#ifndef xihoo_NET_EVENTLOOPTHREAD_H
#define xihoo_NET_EVENTLOOPTHREAD_H

#include "thread/Condition.h"
#include "thread/Mutex.h"
#include "thread/Thread.h"

#include <boost/noncopyable.hpp>

namespace xihoo
{

class EventLoop;

class EventLoopThread : boost::noncopyable
{
 public:
  EventLoopThread();
  ~EventLoopThread();
  EventLoop* startLoop();

 private:
  void threadFunc();

  EventLoop* loop_;
  bool exiting_;
  Thread thread_;
  MutexLock mutex_;
  Condition cond_;
};

}

#endif 


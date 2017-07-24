#ifndef xihoo_NET_TIMERID_H
#define xihoo_NET_TIMERID_H

#include "datetime/copyable.h"

namespace xihoo
{

class Timer;


class TimerId : public xihoo::copyable
{
 public:
  TimerId(Timer* timer = NULL, int64_t seq = 0)
    : timer_(timer),
      sequence_(seq)
  {
  }

 

  friend class TimerQueue;

 private:
  Timer* timer_;
  int64_t sequence_;
};

}

#endif 

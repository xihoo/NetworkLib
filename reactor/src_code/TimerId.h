// excerpts from http://code.google.com/p/xihoo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#ifndef xihoo_NET_TIMERID_H
#define xihoo_NET_TIMERID_H

#include "datetime/copyable.h"

namespace xihoo
{

class Timer;

///
/// An opaque identifier, for canceling Timer.
///
class TimerId : public xihoo::copyable
{
 public:
  TimerId(Timer* timer = NULL, int64_t seq = 0)
    : timer_(timer),
      sequence_(seq)
  {
  }

  // default copy-ctor, dtor and assignment are okay

  friend class TimerQueue;

 private:
  Timer* timer_;
  int64_t sequence_;
};

}

#endif  // xihoo_NET_TIMERID_H

#ifndef xihoo_BASE_LOGGING_H
#define xihoo_BASE_LOGGING_H

#include "LogStream.h"
#include <datetime/Timestamp.h>
#include <boost/scoped_ptr.hpp>

namespace xihoo
{

class Logger
{
 public:
  enum LogLevel
  {
    TRACE,
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL,
    NUM_LOG_LEVELS,
  };

  Logger(const char* file, int line);
  Logger(const char* file, int line, LogLevel level);
  Logger(const char* file, int line, LogLevel level, const char* func);
  Logger(const char* file, int line, bool toAbort);
  ~Logger();

  LogStream& stream() { return impl_.stream_; }

  static LogLevel logLevel();
  static void setLogLevel(LogLevel level);

  typedef void (*OutputFunc)(const char* msg, int len);
  typedef void (*FlushFunc)();
  static void setOutput(OutputFunc);
  static void setFlush(FlushFunc);

 private:

class Impl
{
 public:
  typedef Logger::LogLevel LogLevel;
  Impl(LogLevel level, int old_errno, const char* file, int line);
  void formatTime();
  void finish();

  Timestamp time_;
  LogStream stream_;
  LogLevel level_;
  int line_;
  const char* fullname_;
  const char* basename_;
};

  Impl impl_;

};

#define LOG_TRACE if (xihoo::Logger::logLevel() <= xihoo::Logger::TRACE) \
  xihoo::Logger(__FILE__, __LINE__, xihoo::Logger::TRACE, __func__).stream()
#define LOG_DEBUG if (xihoo::Logger::logLevel() <= xihoo::Logger::DEBUG) \
  xihoo::Logger(__FILE__, __LINE__, xihoo::Logger::DEBUG, __func__).stream()
#define LOG_INFO if (xihoo::Logger::logLevel() <= xihoo::Logger::INFO) \
  xihoo::Logger(__FILE__, __LINE__).stream()
#define LOG_WARN xihoo::Logger(__FILE__, __LINE__, xihoo::Logger::WARN).stream()
#define LOG_ERROR xihoo::Logger(__FILE__, __LINE__, xihoo::Logger::ERROR).stream()
#define LOG_FATAL xihoo::Logger(__FILE__, __LINE__, xihoo::Logger::FATAL).stream()
#define LOG_SYSERR xihoo::Logger(__FILE__, __LINE__, false).stream()
#define LOG_SYSFATAL xihoo::Logger(__FILE__, __LINE__, true).stream()

const char* strerror_tl(int savedErrno);

// Taken from glog/logging.h
//
// Check that the input is non NULL.  This very useful in constructor
// initializer lists.

#define CHECK_NOTNULL(val) \
  ::xihoo::CheckNotNull(__FILE__, __LINE__, "'" #val "' Must be non NULL", (val))

// A small helper for CHECK_NOTNULL().
template <typename T>
T* CheckNotNull(const char *file, int line, const char *names, T* ptr) {
  if (ptr == NULL) {
   Logger(file, line, Logger::FATAL).stream() << names;
  }
  return ptr;
}

template<typename To, typename From>
inline To implicit_cast(From const &f) {
    return f;
}

}

#endif  // xihoo_BASE_LOGGING_H


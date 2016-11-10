
#ifndef _TERMINAL_LOG__H_
#define _TERMINAL_LOG__H_

namespace LRTerminal {
  // Order is the same as retro_log_level
  enum class LogLevel
  {
    DEBUG = 0,
    INFO,
    WARNING,
    ERROR,
  };

  // Log messages, notably for debug purpose
  void log(const LogLevel level, const char* fmt, ...);
}

#endif

#include "terminal_log.h"
#include "terminal_retro.h"

namespace LRTerminal
{
  void log(LogLevel level, const char* fmt, ...)
  {
    va_list args;
    va_start(args, fmt);
    int size = vsnprintf(NULL, 0u, fmt, args);
    va_end(args);

    if (size >= 0)
    {
      char* buff = new char[size + 1];
      va_start(args, fmt);
      (void)vsnprintf(buff, size + 1, fmt, args);
      va_end(args);
      std::string msg = buff;
      delete[] buff;
      LibRetro::getInstance().log(level, msg);
    }
  }
}

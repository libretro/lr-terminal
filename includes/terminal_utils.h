
#ifndef _TERMINAL_UTILS__H_
#define _TERMINAL_UTILS__H_

// Various utility functions

namespace LRTerminal::Utils
{

  template <typename T> T clamp(const T v, const T mn, const T mx)
  {
    T ret = v;
    if (ret < mn)
    {
      ret = mn;
    }
    if (ret > mx)
    {
      ret = mx;
    }
    return ret;
  }

  template <typename T> T lerp(const T a, const T b, const T coef)
  {
    return (a + ((b - a) * coef));
  }

}



#endif

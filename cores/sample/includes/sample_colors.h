
#ifndef _SAMPLE_COLORS__H_
#define _SAMPLE_COLORS__H_

#include "sample_page.h"
#include "terminal_console.h"

namespace Sample
{
  class ColorPage: public Page
  {
  public:
    ColorPage(const unsigned width, const unsigned height);
    virtual ~ColorPage(void);
    virtual void initialize(LRTerminal::Terminal& terminal);
    virtual void update(const double deltaTime);

  private:
    unsigned m_width;
    unsigned m_height;
    LRTerminal::Terminal* m_terminal;
    float m_hue;
  };
}

#endif

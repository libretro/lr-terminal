
#ifndef _SAMPLE_PAGE__H_
#define _SAMPLE_PAGE__H_

namespace LRTerminal
{
  class Terminal;
}

namespace Sample
{
  class Page
  {
  public:
    virtual ~Page(void) {}
    virtual void initialize(LRTerminal::Terminal& terminal) = 0;
    virtual void update(const double deltaTime) = 0;
  };
}

#endif

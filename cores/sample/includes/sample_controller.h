
#ifndef _SAMPLE_CONTROLLER__H_
#define _SAMPLE_CONTROLLER__H_

#include "sample_page.h"
#include <string>

namespace LRTerminal
{
  class TextStyle;
  enum class JoypadKeyInput;
}

namespace Sample
{
  class ShowControlerPage: public Page
  {
  public:
    ShowControlerPage(const unsigned width, const unsigned height);
    ~ShowControlerPage(void);
    virtual void initialize(LRTerminal::Terminal& terminal);
    virtual void update(const double deltaTime);
  private:
    // Print the Status frame
    void _printStatusFrame(const int x, const int y, const LRTerminal::TextStyle& style) const;
    // Print the Controller Figure
    void _printFigure(const int x, const int y, const LRTerminal::TextStyle& style) const;

    // Print the status of a key
    void _printKeyStatus(const int x, const int y, const LRTerminal::TextStyle& style,
                         const std::string& keyName, const LRTerminal::JoypadKeyInput& key) const;
    void _hightlightKey(const int x, const int y, const unsigned w, const unsigned h,
                        const LRTerminal::TextStyle& style, const LRTerminal::JoypadKeyInput& key) const;

    // Front-End to call for various infos (render frame, input state, ...)
    LRTerminal::Terminal* m_terminal;

    // Page size in characters
    unsigned m_width;
    unsigned m_height;
  };
}

#endif


#ifndef _SAMPLE_STYLES__H_
#define _SAMPLE_STYLES__H_

#include "sample_page.h"
#include "terminal_console.h"
#include "terminal_color.h"
#include "terminal_terminal.h"
#include <string>
#include <vector>

namespace Sample
{
  template <typename T> class Selector: public Page
  {
  public:
    Selector(std::string title, const unsigned width, const unsigned height, const int x, const int y):
        m_width(width), m_height(height), m_x(x), m_y(y),
        m_currentIdx(0u), m_console(width, height), m_title(title)
    {}
    virtual ~Selector(void) {}
    virtual void initialize(LRTerminal::Terminal& terminal)
    {
      m_terminal = &terminal;
    }
    virtual void update(const double deltaTime)
    {
      m_console.clear();
      // The selected value has the froeground and background colors reversed
      LRTerminal::TextStyle selected = m_console.getDefaultStyle();
      LRTerminal::Color back = selected.getBackground();
      selected.setBackground(selected.getForeground());
      selected.setForeground(back);
      if (m_hasFocus)
      {
        m_console.printFrame(0, 0, m_width, m_height, false, selected, m_title);
        m_console.rect(1, 1, m_width - 2, m_height - 2, false);
      }
      else
      {
        m_console.printFrame(0, 0, m_width, m_height, false, m_title);
      }

      //
      const int idx = static_cast<int>(m_currentIdx);
      const int minIdx = std::max(0,
                                  std::min(
                                    idx - (static_cast<int>(m_height) / 2),
                                    static_cast<int>(m_values.size()) - (static_cast<int>(m_height) - 2) ));
      const int maxIdx = std::min(static_cast<int>(m_values.size()),
                                  minIdx + (static_cast<int>(m_height) - 2));
      for (int i = minIdx; i < maxIdx; ++i)
      {
        if (i == idx)
        {
          m_console.print(1, i - minIdx + 1, selected, m_values.at(i).first);
        }
        else
        {
          m_console.print(1, i - minIdx + 1, m_values.at(i).first);
        }
      }
      LRTerminal::Console::blit(m_console, 0, 0, m_width, m_height,
                                m_terminal->getRootConsole(), m_x, m_y);
    }
    //
    void addValue(const std::string& name, const T& value)
    {
      m_values.push_back(std::make_pair(name, value));
    }
    const T& getCurrentValue(void) const
    {
      return m_values.at(m_currentIdx).second;
    }
    void setStyle(const LRTerminal::TextStyle& style)
    {
      LRTerminal::TextStyle newStyle = style;
      newStyle.setAlignment(LRTerminal::Alignment::LEFT);
      m_console.setDefaultStyle(newStyle);
    }
    void setFocus(const bool hasFocus)
    {
      m_hasFocus = hasFocus;
    }
    void goPreviousValue(void)
    {
      if (m_currentIdx > 0u)
      {
        --m_currentIdx;
      }
    }
    void goNextValue(void)
    {
      if (m_currentIdx < (m_values.size() - 1u))
      {
        ++m_currentIdx;
      }
    }

  private:
    unsigned m_width;
    unsigned m_height;
    int m_x;
    int m_y;
    bool m_hasFocus;
    LRTerminal::Terminal* m_terminal;
    std::vector<std::pair<std::string, T> > m_values;
    unsigned m_currentIdx;
    LRTerminal::Console m_console;
    std::string m_title;
  };


  class StylesPage: public Page
  {
  public:
    StylesPage(const unsigned width, const unsigned height);
    virtual ~StylesPage(void);
    virtual void initialize(LRTerminal::Terminal& terminal);
    virtual void update(const double deltaTime);

  private:
    unsigned m_width;
    unsigned m_height;
    LRTerminal::Terminal* m_terminal;
    //
    // Selectors
    Selector<LRTerminal::Color> m_backgroundSelector;
    Selector<LRTerminal::Color> m_foregroundSelector;
    Selector<LRTerminal::Font> m_fontSelector;
    Selector<LRTerminal::Alignment> m_alignmentSelector;
    Selector<LRTerminal::LineThickness> m_thicknessSelector;
    //
    enum class Selectors
    {
      BACKGROUND,
      FOREGROUND,
      FONT,
      ALIGNMENT,
      THICKNESS,
    };
    //
    std::vector<Selectors> m_selectors;
    std::vector<Selectors>::iterator m_focusedSelector;
    // For simulating key repeatition
    LRTerminal::JoypadKeyInput m_lastKey;
    double m_lastKeyDownTick;
    bool m_keyDown;
  };
}


#endif

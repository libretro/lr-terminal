#include "sample_colors.h"
#include "terminal_terminal.h"
#include "terminal_console.h"
#include "terminal_color.h"
#include <cmath>

using namespace LRTerminal;

namespace Sample
{
  ColorPage::ColorPage(const unsigned width, const unsigned height):
      m_width(width), m_height(height),
      m_hue(0.0f)
  {
  }

  ColorPage::~ColorPage(void)
  {
  }

  void ColorPage::initialize(LRTerminal::Terminal& terminal)
  {
    m_terminal = &terminal;
  }

  void ColorPage::update(const double deltaTime)
  {
    Console& rootConsole = m_terminal->getRootConsole();
    LRTerminal::TextStyle style = rootConsole.getDefaultStyle();
    style.setBackground(Color::darkestGrey);
    style.setForeground(Color::lightestGrey);
    rootConsole.setDefaultStyle(style);
    rootConsole.clear();
    style.setAlignment(Alignment::CENTER);
    rootConsole.print(m_width / 2, 0, style, "Color test page");
    //
    rootConsole.print(m_width / 4, 2, style, "HSL");
    rootConsole.print(3 * m_width / 4, 2, style, "HSV");
    //
    m_hue = fmodf(m_hue + 10.0 * deltaTime, 360.0);
    //
    for (unsigned j = 2u; j < m_height - 2u; ++j)
    {
      for (unsigned i = 2u; i < (m_width - 2u) / 2u; ++i)
      {
        rootConsole.setBackground(i, j,
                                  Color::fromHSL(m_hue,
                                                 100.0 * 2 * (i - 2) / (m_width - 4),
                                                 100.0 * (j - 2) / (m_height - 4)));
        rootConsole.setBackground(i + (m_width - 2) / 2, j,
                                  Color::fromHSV(m_hue,
                                                 100.0 * 2 * (i - 2) / (m_width - 4),
                                                 100.0 * (j - 2) / (m_height - 4)));
      }
    }

  }


}

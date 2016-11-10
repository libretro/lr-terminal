#include "sample_controller.h"
#include "terminal_terminal.h"
#include "terminal_color.h"
#include "terminal_console.h"

using namespace LRTerminal;

namespace Sample
{
  // Controller Page
  ShowControlerPage::ShowControlerPage(const unsigned width, const unsigned height):
      m_width(width), m_height(height)
  {
  }
  ShowControlerPage::~ShowControlerPage(void)
  {
  }
  void ShowControlerPage::initialize(LRTerminal::Terminal& terminal)
  {
    m_terminal = &terminal;
  }
  void ShowControlerPage::update(const double deltaTime)
  {
    Console& rootConsole = m_terminal->getRootConsole();
    LRTerminal::TextStyle style = rootConsole.getDefaultStyle();
    style.setBackground(Color::darkestSepia);
    style.setForeground(Color::lightestSepia);
    rootConsole.setDefaultStyle(style);
    rootConsole.clear();
    style.setAlignment(Alignment::CENTER);
    rootConsole.print(m_width / 2, 0, style, "Controller test page");
    //
    // Left frame
    style.setBackground(Color::darkestGrey);
    style.setForeground(Color::lightestGrey);
    _printStatusFrame(2, 2, style);
    //
    style.setBackground(Color::darkestSepia);
    style.setForeground(Color::lightestSepia);
    _printFigure(30, 8, style);
  }

  // Print the Status frame
  void ShowControlerPage::_printStatusFrame(const int x, const int y, const LRTerminal::TextStyle& style) const
  {
    Console& rootConsole = m_terminal->getRootConsole();
    TextStyle txtStyle = style;
    txtStyle.setAlignment(Alignment::CENTER);
    txtStyle.setLineThickness(LineThickness::DOUBLE);
    rootConsole.printFrame(x, y, 15u, 14u, false, txtStyle, "Status");
    int nx = x + 2;
    int ny =  y + 1;
    txtStyle.setAlignment(Alignment::LEFT);
    _printKeyStatus(nx, ny++, txtStyle, "Up", JoypadKeyInput::UP);
    _printKeyStatus(nx, ny++, txtStyle, "Down", JoypadKeyInput::DOWN);
    _printKeyStatus(nx, ny++, txtStyle, "Left", JoypadKeyInput::LEFT);
    _printKeyStatus(nx, ny++, txtStyle, "Right", JoypadKeyInput::RIGHT);
    _printKeyStatus(nx, ny++, txtStyle, "A", JoypadKeyInput::A);
    _printKeyStatus(nx, ny++, txtStyle, "B", JoypadKeyInput::B);
    _printKeyStatus(nx, ny++, txtStyle, "X", JoypadKeyInput::X);
    _printKeyStatus(nx, ny++, txtStyle, "Y", JoypadKeyInput::Y);
    _printKeyStatus(nx, ny++, txtStyle, "L", JoypadKeyInput::L);
    _printKeyStatus(nx, ny++, txtStyle, "R", JoypadKeyInput::R);
    _printKeyStatus(nx, ny++, txtStyle, "START", JoypadKeyInput::START);
    _printKeyStatus(nx, ny++, txtStyle, "SELECT", JoypadKeyInput::SELECT);

  }

  // Print the Controller Figure
  void ShowControlerPage::_printFigure(const int x, const int y, const LRTerminal::TextStyle& style) const
  {
    Console& rootConsole = m_terminal->getRootConsole();
    TextStyle txtStyle = style;
    txtStyle.setAlignment(Alignment::LEFT);
    // Controller figure
    int nx = x;
    int ny = y;
    rootConsole.print(nx, ny++, txtStyle, " ╭──────╮            ╭──────╮ ");
    rootConsole.print(nx, ny++, txtStyle, "╭┴──────┴────────────┴──────┴╮");
    rootConsole.print(nx, ny++, txtStyle, "│  ┌─┐                 ╭─╮   │");
    rootConsole.print(nx, ny++, txtStyle, "│┌─┘ └─┐    ╭╮  ╭╮  ╭─╮╰─╯╭─╮│");
    rootConsole.print(nx, ny++, txtStyle, "│└─┐ ┌─┘    ╰╯  ╰╯  ╰─╯╭─╮╰─╯│");
    rootConsole.print(nx, ny++, txtStyle, "│  └─┘                 ╰─╯   │");
    rootConsole.print(nx, ny++, txtStyle, "│       ╭────────────╮       │");
    rootConsole.print(nx, ny++, txtStyle, "╰───────╯            ╰───────╯");
    // Special style used to hightlight the buttons on the figure when those are down
    txtStyle.setForeground(Color::fromRGB(0, 255, 0));
    _hightlightKey(x + 1, y, 8, 2, txtStyle, JoypadKeyInput::L);
    _hightlightKey(x + 21, y, 8, 2, txtStyle, JoypadKeyInput::R);
    _hightlightKey(x + 3, y + 2, 3, 2, txtStyle, JoypadKeyInput::UP);
    _hightlightKey(x + 1, y + 3, 3, 2, txtStyle, JoypadKeyInput::LEFT);
    _hightlightKey(x + 5, y + 3, 3, 2, txtStyle, JoypadKeyInput::RIGHT);
    _hightlightKey(x + 3, y + 4, 3, 2, txtStyle, JoypadKeyInput::DOWN);
    _hightlightKey(x + 12, y + 3, 2, 2, txtStyle, JoypadKeyInput::SELECT);
    _hightlightKey(x + 16, y + 3, 2, 2, txtStyle, JoypadKeyInput::START);
    _hightlightKey(x + 23, y + 2, 3, 2, txtStyle, JoypadKeyInput::X);
    _hightlightKey(x + 20, y + 3, 3, 2, txtStyle, JoypadKeyInput::Y);
    _hightlightKey(x + 26, y + 3, 3, 2, txtStyle, JoypadKeyInput::A);
    _hightlightKey(x + 23, y + 4, 3, 2, txtStyle, JoypadKeyInput::B);
  }

  void ShowControlerPage::_hightlightKey(const int x, const int y, const unsigned w, const unsigned h,
                                         const LRTerminal::TextStyle& style,
                                         const LRTerminal::JoypadKeyInput& key) const
  {
    if (m_terminal->isKeyDown(PlayerInput::PLAYER_1, key))
    {
      Console& rootConsole = m_terminal->getRootConsole();
      for (unsigned j = 0u; j < h; ++j)
      {
        for (unsigned i = 0u; i < w; ++i)
        {
          rootConsole.setStyle(x + i, y + j, style);
        }
      }
    }
  }

  // Print the status of a key
  void ShowControlerPage::_printKeyStatus(const int x, const int y, const LRTerminal::TextStyle& style,
                                          const std::string& keyName,
                                          const LRTerminal::JoypadKeyInput& key) const
  {
    Console& rootConsole = m_terminal->getRootConsole();
    rootConsole.print(
      x, y, style, "%s: %s",
      keyName.c_str(),
      m_terminal->isKeyDown(PlayerInput::PLAYER_1, key) ? "DOWN" : "UP"
    );
  }
}

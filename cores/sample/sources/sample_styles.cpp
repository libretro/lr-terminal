#include "sample_styles.h"

namespace Sample
{
  StylesPage::StylesPage(const unsigned width, const unsigned height):
      m_width(width), m_height(height),
      m_backgroundSelector("Background", width / 5, (height / 2) - 3, 0, 1),
      m_foregroundSelector("Foreground", width / 5, (height / 2) - 3, width / 5, 1),
      m_fontSelector("Font", width / 5, (height / 2) - 3, 2 * width / 5, 1),
      m_alignmentSelector("Alignment", width / 5, (height / 2) - 3, 3 * width / 5, 1),
      m_thicknessSelector("Line", width / 5, (height / 2) - 3, 4 * width / 5, 1),
      m_lastKey(LRTerminal::JoypadKeyInput::B), m_lastKeyDownTick(0.0),
      m_keyDown(false)
  {
    m_selectors.push_back(Selectors::BACKGROUND);
    m_selectors.push_back(Selectors::FOREGROUND);
    m_selectors.push_back(Selectors::FONT);
    m_selectors.push_back(Selectors::ALIGNMENT);
    m_selectors.push_back(Selectors::THICKNESS);
    //
    m_focusedSelector = m_selectors.begin();
    // Fill the selectors and select the default

    // Background
    m_backgroundSelector.addValue("Black", LRTerminal::Color::black);
    m_backgroundSelector.addValue("White", LRTerminal::Color::white);
    m_backgroundSelector.addValue("Grey", LRTerminal::Color::grey);
    m_backgroundSelector.addValue("Sepia", LRTerminal::Color::sepia);
    m_backgroundSelector.addValue("Red", LRTerminal::Color::red);
    m_backgroundSelector.addValue("Flame", LRTerminal::Color::flame);
    m_backgroundSelector.addValue("Orange", LRTerminal::Color::orange);
    m_backgroundSelector.addValue("Amber", LRTerminal::Color::amber);
    m_backgroundSelector.addValue("Yellow", LRTerminal::Color::yellow);
    m_backgroundSelector.addValue("Lime", LRTerminal::Color::lime);
    m_backgroundSelector.addValue("Chartreuse", LRTerminal::Color::chartreuse);
    m_backgroundSelector.addValue("Green", LRTerminal::Color::green);
    m_backgroundSelector.addValue("Sea", LRTerminal::Color::sea);
    m_backgroundSelector.addValue("Turquoise", LRTerminal::Color::turquoise);
    m_backgroundSelector.addValue("Cyan", LRTerminal::Color::cyan);
    m_backgroundSelector.addValue("Sky", LRTerminal::Color::sky);
    m_backgroundSelector.addValue("Azure", LRTerminal::Color::azure);
    m_backgroundSelector.addValue("Blue", LRTerminal::Color::blue);
    m_backgroundSelector.addValue("Han", LRTerminal::Color::han);
    m_backgroundSelector.addValue("Violet", LRTerminal::Color::violet);
    m_backgroundSelector.addValue("Purple", LRTerminal::Color::purple);
    m_backgroundSelector.addValue("Fuchsia", LRTerminal::Color::fuchsia);
    m_backgroundSelector.addValue("Magenta", LRTerminal::Color::magenta);
    m_backgroundSelector.addValue("Pink", LRTerminal::Color::pink);
    m_backgroundSelector.addValue("Crimson", LRTerminal::Color::crimson);
    // Default is black

    // Foreground
    m_foregroundSelector.addValue("Black", LRTerminal::Color::black);
    m_foregroundSelector.addValue("White", LRTerminal::Color::white);
    m_foregroundSelector.addValue("Grey", LRTerminal::Color::grey);
    m_foregroundSelector.addValue("Sepia", LRTerminal::Color::sepia);
    m_foregroundSelector.addValue("Red", LRTerminal::Color::red);
    m_foregroundSelector.addValue("Flame", LRTerminal::Color::flame);
    m_foregroundSelector.addValue("Orange", LRTerminal::Color::orange);
    m_foregroundSelector.addValue("Amber", LRTerminal::Color::amber);
    m_foregroundSelector.addValue("Yellow", LRTerminal::Color::yellow);
    m_foregroundSelector.addValue("Lime", LRTerminal::Color::lime);
    m_foregroundSelector.addValue("Chartreuse", LRTerminal::Color::chartreuse);
    m_foregroundSelector.addValue("Green", LRTerminal::Color::green);
    m_foregroundSelector.addValue("Sea", LRTerminal::Color::sea);
    m_foregroundSelector.addValue("Turquoise", LRTerminal::Color::turquoise);
    m_foregroundSelector.addValue("Cyan", LRTerminal::Color::cyan);
    m_foregroundSelector.addValue("Sky", LRTerminal::Color::sky);
    m_foregroundSelector.addValue("Azure", LRTerminal::Color::azure);
    m_foregroundSelector.addValue("Blue", LRTerminal::Color::blue);
    m_foregroundSelector.addValue("Han", LRTerminal::Color::han);
    m_foregroundSelector.addValue("Violet", LRTerminal::Color::violet);
    m_foregroundSelector.addValue("Purple", LRTerminal::Color::purple);
    m_foregroundSelector.addValue("Fuchsia", LRTerminal::Color::fuchsia);
    m_foregroundSelector.addValue("Magenta", LRTerminal::Color::magenta);
    m_foregroundSelector.addValue("Pink", LRTerminal::Color::pink);
    m_foregroundSelector.addValue("Crimson", LRTerminal::Color::crimson);
    // Default is white
    m_foregroundSelector.goNextValue();

    // Font selector
    m_fontSelector.addValue("Default", LRTerminal::Font::DEFAULT);
    m_fontSelector.addValue("Tamsyn R", LRTerminal::Font::TAMSYN_REGULAR);
    m_fontSelector.addValue("Tamsyn B", LRTerminal::Font::TAMSYN_BOLD);
    m_fontSelector.addValue("8x16", LRTerminal::Font::SONY_MISC_8x16);
    m_fontSelector.addValue("8x13", LRTerminal::Font::MISC_MISC_8x13);
    m_fontSelector.addValue("8x13 B", LRTerminal::Font::MISC_MISC_8x13_BOLD);
    m_fontSelector.addValue("8x13 O", LRTerminal::Font::MISC_MISC_8x13_OBLIQUE);
    // Default is Default

    // Alignment selector
    m_alignmentSelector.addValue("Left", LRTerminal::Alignment::LEFT);
    m_alignmentSelector.addValue("Center", LRTerminal::Alignment::CENTER);
    m_alignmentSelector.addValue("Right", LRTerminal::Alignment::RIGHT);
    // Default is Left

    // Line Thickness
    m_thicknessSelector.addValue("Light", LRTerminal::LineThickness::LIGHT);
    m_thicknessSelector.addValue("Heavy", LRTerminal::LineThickness::HEAVY);
    m_thicknessSelector.addValue("Double", LRTerminal::LineThickness::DOUBLE);
  }

  StylesPage::~StylesPage(void)
  {
  }

  void StylesPage::initialize(LRTerminal::Terminal& terminal)
  {
    m_terminal = &terminal;
    m_backgroundSelector.initialize(terminal);
    m_foregroundSelector.initialize(terminal);
    m_fontSelector.initialize(terminal);
    m_alignmentSelector.initialize(terminal);
    m_thicknessSelector.initialize(terminal);
  }

  void StylesPage::update(const double deltaTime)
  {
    // Check the key presses
    bool up = m_terminal->isKeyDown(LRTerminal::PlayerInput::PLAYER_1, LRTerminal::JoypadKeyInput::UP);
    bool down = m_terminal->isKeyDown(LRTerminal::PlayerInput::PLAYER_1, LRTerminal::JoypadKeyInput::DOWN);
    bool R = m_terminal->isKeyDown(LRTerminal::PlayerInput::PLAYER_1, LRTerminal::JoypadKeyInput::R);
    bool L = m_terminal->isKeyDown(LRTerminal::PlayerInput::PLAYER_1, LRTerminal::JoypadKeyInput::L);
    if (up)
    {
      bool goPrev = false;
      if (m_keyDown && (m_lastKey == LRTerminal::JoypadKeyInput::UP) && (m_lastKeyDownTick > 0.5))
      {
        // Repeat key
        goPrev = true;
        m_lastKeyDownTick = 0.0;
      }
      else if (m_keyDown && (m_lastKey == LRTerminal::JoypadKeyInput::UP))
      {
        m_lastKeyDownTick += deltaTime;
      }
      else if (!m_keyDown)
      {
        m_keyDown = true;
        m_lastKey = LRTerminal::JoypadKeyInput::UP;
        goPrev = true;
      }
      if (goPrev)
      {
        switch(*m_focusedSelector)
        {
          case Selectors::BACKGROUND:
            m_backgroundSelector.goPreviousValue();
            break;
          case Selectors::FOREGROUND:
            m_foregroundSelector.goPreviousValue();
            break;
          case Selectors::FONT:
            m_fontSelector.goPreviousValue();
            break;
          case Selectors::ALIGNMENT:
            m_alignmentSelector.goPreviousValue();
            break;
          case Selectors::THICKNESS:
            m_thicknessSelector.goPreviousValue();
            break;
          default:
            break;
        }
      }
    }
    if (down)
    {
      bool goNext = false;
      if (m_keyDown && (m_lastKey == LRTerminal::JoypadKeyInput::DOWN) && (m_lastKeyDownTick > 0.5))
      {
        // Repeat key
        goNext = true;
        m_lastKeyDownTick = 0.0;
      }
      else if (m_keyDown && (m_lastKey == LRTerminal::JoypadKeyInput::DOWN))
      {
        m_lastKeyDownTick += deltaTime;
      }
      else if (!m_keyDown)
      {
        m_keyDown = true;
        m_lastKey = LRTerminal::JoypadKeyInput::DOWN;
        goNext = true;
      }
      if (goNext)
      {
        switch(*m_focusedSelector)
        {
          case Selectors::BACKGROUND:
            m_backgroundSelector.goNextValue();
            break;
          case Selectors::FOREGROUND:
            m_foregroundSelector.goNextValue();
            break;
          case Selectors::FONT:
            m_fontSelector.goNextValue();
            break;
          case Selectors::ALIGNMENT:
            m_alignmentSelector.goNextValue();
            break;
          case Selectors::THICKNESS:
            m_thicknessSelector.goNextValue();
            break;
          default:
            break;
        }
      }
    }
    if (L)
    {
      bool focusPrev = false;
      if (m_keyDown && (m_lastKey == LRTerminal::JoypadKeyInput::L) && (m_lastKeyDownTick > 0.5))
      {
        // Repeat key
        focusPrev = true;
        m_lastKeyDownTick = 0.0;
      }
      else if (m_keyDown && (m_lastKey == LRTerminal::JoypadKeyInput::L))
      {
        m_lastKeyDownTick += deltaTime;
      }
      else if (!m_keyDown)
      {
        m_keyDown = true;
        m_lastKey = LRTerminal::JoypadKeyInput::L;
        focusPrev = true;
      }
      if (focusPrev)
      {
        if (m_focusedSelector == m_selectors.begin())
        {
          m_focusedSelector = m_selectors.end();
        }
        --m_focusedSelector;
      }
    }
    if (R)
    {
      bool focusNext = false;
      if (m_keyDown && (m_lastKey == LRTerminal::JoypadKeyInput::R) && (m_lastKeyDownTick > 0.5))
      {
        // Repeat key
        focusNext = true;
        m_lastKeyDownTick = 0.0;
      }
      else if (m_keyDown && (m_lastKey == LRTerminal::JoypadKeyInput::R))
      {
        m_lastKeyDownTick += deltaTime;
      }
      else if (!m_keyDown)
      {
        m_keyDown = true;
        m_lastKey = LRTerminal::JoypadKeyInput::R;
        focusNext = true;
      }
      if (focusNext)
      {
        ++m_focusedSelector;
        if (m_focusedSelector == m_selectors.end())
        {
          m_focusedSelector = m_selectors.begin();
        }
      }
    }
    if (!(up || down || L || R))
    {
      m_keyDown = false;
      m_lastKeyDownTick = 0.0;
    }

    // Set the focus
    m_backgroundSelector.setFocus(false);
    m_foregroundSelector.setFocus(false);
    m_fontSelector.setFocus(false);
    m_alignmentSelector.setFocus(false);
    m_thicknessSelector.setFocus(false);
    switch(*m_focusedSelector)
    {
      case Selectors::BACKGROUND:
        m_backgroundSelector.setFocus(true);
        break;
      case Selectors::FOREGROUND:
        m_foregroundSelector.setFocus(true);
        break;
      case Selectors::FONT:
        m_fontSelector.setFocus(true);
        break;
      case Selectors::ALIGNMENT:
        m_alignmentSelector.setFocus(true);
        break;
      case Selectors::THICKNESS:
        m_thicknessSelector.setFocus(true);
        break;
      default:
        break;
    }
    //
    LRTerminal::Console& rootConsole = m_terminal->getRootConsole();
    LRTerminal::TextStyle style = rootConsole.getDefaultStyle();
    style.setBackground(LRTerminal::Color::darkestGrey);
    style.setForeground(LRTerminal::Color::lightestGrey);
    rootConsole.setDefaultStyle(style);
    rootConsole.clear();
    m_backgroundSelector.setStyle(style);
    m_foregroundSelector.setStyle(style);
    m_fontSelector.setStyle(style);
    m_alignmentSelector.setStyle(style);
    m_thicknessSelector.setStyle(style);
    //
    style.setAlignment(LRTerminal::Alignment::CENTER);
    rootConsole.print(m_width / 2, 0, style, "Style test page");
    rootConsole.print(m_width / 2, m_height - 2, style,
                      "Up/Down to select in current category. L/R to change category.");
    //
    m_backgroundSelector.update(deltaTime);
    m_foregroundSelector.update(deltaTime);
    m_fontSelector.update(deltaTime);
    m_alignmentSelector.update(deltaTime);
    m_thicknessSelector.update(deltaTime);
    //
    style.setBackground(m_backgroundSelector.getCurrentValue());
    style.setForeground(m_foregroundSelector.getCurrentValue());
    style.setFont(m_fontSelector.getCurrentValue());
    style.setAlignment(m_alignmentSelector.getCurrentValue());
    style.setLineThickness(m_thicknessSelector.getCurrentValue());
    //
    rootConsole.printFrame(0, m_height / 2 - 2, m_width, m_height / 2, true, style);
    rootConsole.printRect(
      1, m_height / 2 - 1, m_width - 2u, (m_height / 2u) - 2u, false, style,
      "The quick brown fox jumps over the lazy dog. "
      "Voix ambigüe d'un cœur qui, au zéphir, préfère les jattes de kiwi."
    );
  }
}

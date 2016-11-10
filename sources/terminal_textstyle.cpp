#include "terminal_textstyle.h"

namespace LRTerminal
{
    ////
  // TextStyle
  TextStyle::TextStyle():
      m_background(0u, 0u, 0u), m_foreground(0u, 0u, 0u),
      m_font(Font::DEFAULT), m_backgroundFlag(BackgroundFlag::SET),
      m_alignment(Alignment::LEFT), m_lineThickness(LineThickness::LIGHT)
  {
  }

  TextStyle::TextStyle(const TextStyle& that):
      m_background(that.getBackground()), m_foreground(that.getForeground()),
      m_font(that.getFont()), m_backgroundFlag(that.getBackgroundFlag()),
      m_alignment(that.getAlignment()), m_lineThickness(that.getLineThickness())
  {
  }

  TextStyle& TextStyle::operator=(const TextStyle& that)
  {
    m_background = that.getBackground();
    m_foreground = that.getForeground();
    m_font = that.getFont();
    m_backgroundFlag = that.getBackgroundFlag();
    m_alignment = that.getAlignment();
    m_lineThickness = that.getLineThickness();
    return *this;
  }

  // Setters
  void TextStyle::setBackground(const Color& col)
  {
    m_background = col;
  }

  void TextStyle::setForeground(const Color& col)
  {
    m_foreground = col;
  }

  void TextStyle::setFont(const Font font)
  {
    m_font = font;
  }

  void TextStyle::setBackgroundFlag(const BackgroundFlag flag)
  {
    m_backgroundFlag = flag;
  }

  void TextStyle::setAlignment(const Alignment align)
  {
    m_alignment = align;
  }

  void TextStyle::setLineThickness(const LineThickness thickness)
  {
    m_lineThickness = thickness;
  }

  // Getters
  const Color& TextStyle::getBackground(void) const
  {
    return m_background;
  }

  const Color& TextStyle::getForeground(void) const
  {
    return m_foreground;
  }

  Font TextStyle::getFont(void) const
  {
    return m_font;
  }

  BackgroundFlag TextStyle::getBackgroundFlag(void) const
  {
    return m_backgroundFlag;
  }

  Alignment TextStyle::getAlignment(void) const
  {
    return m_alignment;
  }

  LineThickness TextStyle::getLineThickness(void) const
  {
    return m_lineThickness;
  }

  // For box-drawing
  static std::map<LineThickness, std::map<BoxDrawing, char32_t> > s_BoxDrawingChars;
  char32_t _getBoxDrawingCharacter(const LineThickness thickness, const BoxDrawing boxDrawing)
  {
    // Fill the map on the first call
    if (s_BoxDrawingChars.empty())
    {
      // LIGHT
      s_BoxDrawingChars[LineThickness::LIGHT][BoxDrawing::HORIZONTAL] = U'─';
      s_BoxDrawingChars[LineThickness::LIGHT][BoxDrawing::VERTICAL] = U'│';
      s_BoxDrawingChars[LineThickness::LIGHT][BoxDrawing::DOWN_AND_RIGHT] = U'┌';
      s_BoxDrawingChars[LineThickness::LIGHT][BoxDrawing::DOWN_AND_LEFT] = U'┐';
      s_BoxDrawingChars[LineThickness::LIGHT][BoxDrawing::UP_AND_RIGHT] = U'└';
      s_BoxDrawingChars[LineThickness::LIGHT][BoxDrawing::UP_AND_LEFT] = U'┘';
      s_BoxDrawingChars[LineThickness::LIGHT][BoxDrawing::VERTICAL_AND_RIGHT] = U'├';
      s_BoxDrawingChars[LineThickness::LIGHT][BoxDrawing::VERTICAL_AND_LEFT] = U'┤';
      s_BoxDrawingChars[LineThickness::LIGHT][BoxDrawing::DOWN_AND_HORIZONTAL] = U'┬';
      s_BoxDrawingChars[LineThickness::LIGHT][BoxDrawing::UP_AND_HORIZONTAL] = U'┴';
      s_BoxDrawingChars[LineThickness::LIGHT][BoxDrawing::VERTICAL_AND_HORIZONTAL] = U'┼';
      // HEAVY
      s_BoxDrawingChars[LineThickness::HEAVY][BoxDrawing::HORIZONTAL] = U'━';
      s_BoxDrawingChars[LineThickness::HEAVY][BoxDrawing::VERTICAL] = U'┃';
      s_BoxDrawingChars[LineThickness::HEAVY][BoxDrawing::DOWN_AND_RIGHT] = U'┏';
      s_BoxDrawingChars[LineThickness::HEAVY][BoxDrawing::DOWN_AND_LEFT] = U'┓';
      s_BoxDrawingChars[LineThickness::HEAVY][BoxDrawing::UP_AND_RIGHT] = U'┗';
      s_BoxDrawingChars[LineThickness::HEAVY][BoxDrawing::UP_AND_LEFT] = U'┛';
      s_BoxDrawingChars[LineThickness::HEAVY][BoxDrawing::VERTICAL_AND_RIGHT] = U'┣';
      s_BoxDrawingChars[LineThickness::HEAVY][BoxDrawing::VERTICAL_AND_LEFT] = U'┫';
      s_BoxDrawingChars[LineThickness::HEAVY][BoxDrawing::DOWN_AND_HORIZONTAL] = U'┳';
      s_BoxDrawingChars[LineThickness::HEAVY][BoxDrawing::UP_AND_HORIZONTAL] = U'┻';
      s_BoxDrawingChars[LineThickness::HEAVY][BoxDrawing::VERTICAL_AND_HORIZONTAL] = U'╋';
      // DOUBLE
      s_BoxDrawingChars[LineThickness::DOUBLE][BoxDrawing::HORIZONTAL] = U'═';
      s_BoxDrawingChars[LineThickness::DOUBLE][BoxDrawing::VERTICAL] = U'║';
      s_BoxDrawingChars[LineThickness::DOUBLE][BoxDrawing::DOWN_AND_RIGHT] = U'╔';
      s_BoxDrawingChars[LineThickness::DOUBLE][BoxDrawing::DOWN_AND_LEFT] = U'╗';
      s_BoxDrawingChars[LineThickness::DOUBLE][BoxDrawing::UP_AND_RIGHT] = U'╚';
      s_BoxDrawingChars[LineThickness::DOUBLE][BoxDrawing::UP_AND_LEFT] = U'╝';
      s_BoxDrawingChars[LineThickness::DOUBLE][BoxDrawing::VERTICAL_AND_RIGHT] = U'╠';
      s_BoxDrawingChars[LineThickness::DOUBLE][BoxDrawing::VERTICAL_AND_LEFT] = U'╣';
      s_BoxDrawingChars[LineThickness::DOUBLE][BoxDrawing::DOWN_AND_HORIZONTAL] = U'╦';
      s_BoxDrawingChars[LineThickness::DOUBLE][BoxDrawing::UP_AND_HORIZONTAL] = U'╩';
      s_BoxDrawingChars[LineThickness::DOUBLE][BoxDrawing::VERTICAL_AND_HORIZONTAL] = U'╬';
    }
    return s_BoxDrawingChars.at(thickness).at(boxDrawing);
  }

  char32_t TextStyle::getBoxDrawingCharacter(const BoxDrawing boxDrawing) const
  {
    return _getBoxDrawingCharacter(m_lineThickness, boxDrawing);
  }
}

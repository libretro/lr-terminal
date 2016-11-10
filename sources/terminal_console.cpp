#include "terminal_console.h"
#include <locale>
#include <codecvt>

namespace LRTerminal
{

  ////
  // Console cell
  Console::ConsoleCell::ConsoleCell():
      m_background(0u, 0u, 0u), m_foreground(0u, 0u, 0u),
      m_codePoint(0u), m_font(Font::DEFAULT),
      m_isDirty(true)
  {
  }

  const Color& Console::ConsoleCell::getBackground(void) const
  {
    return m_background;
  }

  const Color& Console::ConsoleCell::getForeground(void) const
  {
    return m_foreground;
  }

  char32_t Console::ConsoleCell::getCodePoint(void) const
  {
    return m_codePoint;
  }

  Font Console::ConsoleCell::getFont(void) const
  {
    return m_font;
  }

  bool Console::ConsoleCell::isDirty(void) const
  {
    return m_isDirty;
  }

  bool Console::ConsoleCell::isBlank(void) const
  {
    // A cell is considered blank if the code point corresponds to Nul or Space
    return (m_codePoint == U'\0') || (m_codePoint == U' ');
  }

  void Console::ConsoleCell::setForeground(const Color& color)
  {
    if (m_foreground != color)
    {
      m_foreground = color;
      m_isDirty = true;
    }
  }

  void Console::ConsoleCell::setBackground(const Color& color, const BackgroundFlag flag)
  {
    Color newColor;
    switch (flag)
    {
      case BackgroundFlag::SET:
        newColor = color;
        break;
      case BackgroundFlag::MULTIPLY:
        newColor = m_background * color;
        break;
      case BackgroundFlag::LIGHTEN:
        newColor = Color::lighten(m_background, color);
        break;
      case BackgroundFlag::DARKEN:
        newColor = Color::darken(m_background, color);
        break;
      case BackgroundFlag::SCREEN:
        newColor = Color::screen(m_background, color);
        break;
      case BackgroundFlag::COLOR_DODGE:
        newColor = Color::colorDodge(m_background, color);
        break;
      case BackgroundFlag::COLOR_BURN:
        newColor = Color::colorBurn(m_background, color);
        break;
      case BackgroundFlag::ADD:
        newColor = m_background + color;
        break;
      case BackgroundFlag::BURN:
        newColor = Color::burn(m_background, color);
        break;
      case BackgroundFlag::OVERLAY:
        newColor = Color::overlay(m_background, color);
        break;
      case BackgroundFlag::NONE:
      default:
        newColor = m_background;
        break;
    }
    if (m_background != newColor)
    {
      m_background = newColor;
      m_isDirty = true;
    }
  }

  void Console::ConsoleCell::setCodePoint(const char32_t codePoint)
  {
    if (m_codePoint != codePoint)
    {
      m_codePoint = codePoint;
      m_isDirty = true;
    }
  }

  void Console::ConsoleCell::setFont(const Font font)
  {
    if (m_font != font)
    {
      m_font = font;
      m_isDirty = true;
    }
  }

  void Console::ConsoleCell::unsetDirty(void)
  {
    m_isDirty = false;
  }

  ////
  // Console
  // Constructor, destructor
  Console::Console(const unsigned width, const unsigned height):
      m_width(width), m_height(height), m_defaultStyle(),
      m_isIgnoreCellColorEnabled(false), m_ignoreCellColor()
  {
    m_cells.resize(m_width * m_height);
  }

  Console::~Console()
  {
    m_cells.clear();
  }

  // Default Style
  void Console::setDefaultStyle(const TextStyle& style)
  {
    m_defaultStyle = style;
  }
  // Default colors when cleared
  void Console::setDefaultBackground(const Color& col)
  {
    m_defaultStyle.setBackground(col);
  }
  void Console::setDefaultForeground(const Color& col)
  {
    m_defaultStyle.setForeground(col);
  }
  // Set the default background flag
  void Console::setBackgroundFlag(const BackgroundFlag flag)
  {
    m_defaultStyle.setBackgroundFlag(flag);
  }
  // Set the default text alignment
  void Console::setAlignment(const Alignment align)
  {
    m_defaultStyle.setAlignment(align);
  }
  // Set the default font
  void Console::setDefaultFont(const Font font)
  {
    m_defaultStyle.setFont(font);
  }


  // Clear the console: set all characters to nul and the colors to the default colors
  void Console::clear(void)
  {
    for (auto iter = m_cells.begin(); iter != m_cells.end(); ++iter)
    {
      iter->setCodePoint(0u);
      iter->setForeground(m_defaultStyle.getForeground());
      iter->setBackground(m_defaultStyle.getBackground());
      iter->setFont(m_defaultStyle.getFont());
    }
  }

  // Set the codepoint of a cell
  void Console::setChar(const int x, const int y, const char32_t c)
  {
    if (_isInside(x, y))
    {
      m_cells[_cellIndex(x, y)].setCodePoint(c);
    }
  }
  // Set all the properties of a cell
  void Console::setChar(const int x, const int y, const char32_t c, const TextStyle& style)
  {
    if (_isInside(x, y))
    {
      m_cells[_cellIndex(x, y)].setCodePoint(c);
      m_cells[_cellIndex(x, y)].setForeground(style.getForeground());
      m_cells[_cellIndex(x, y)].setBackground(style.getBackground(), style.getBackgroundFlag());
      m_cells[_cellIndex(x, y)].setFont(style.getFont());
    }
  }
  // Set the style of a char
  void Console::setStyle(const int x, const int y, const TextStyle& style)
  {
    if (_isInside(x, y))
    {
      setChar(x, y, getChar(x, y), style);
    }
  }
  // Set the background color of a cell
  void Console::setBackground(const int x, const int y, const Color& col,
                              const BackgroundFlag flag)
  {
    if (_isInside(x, y))
    {
      m_cells[_cellIndex(x, y)].setBackground(col, flag);
    }
  }
  // Set the foreground color of a cell
  void Console::setForeground(const int x, const int y, const Color& col)
  {
    if (_isInside(x, y))
    {
      m_cells[_cellIndex(x, y)].setForeground(col);
    }
  }
  // Set the font of a cell
  void Console::setFont(const int x, const int y, const Font font)
  {
    if (_isInside(x, y))
    {
      m_cells[_cellIndex(x, y)].setFont(font);
    }
  }

  // Print a formatted string with default style
  void Console::print(const int x, const int y, const char* fmt, ...)
  {
    va_list args;
    va_start(args, fmt);
    int size = _computeStringSize(fmt, args);
    va_end(args);
    va_start(args, fmt);
    std::string str = _computeString(size, fmt, args);
    va_end(args);
    print(x, y, m_defaultStyle, _stringToU32String(str));
  }
  // Print an utf-8 string with default style
  void Console::print(const int x, const int y, const std::string& str)
  {
    print(x, y, m_defaultStyle, _stringToU32String(str));
  }
  // Print an utf-32 string with default style
  void Console::print(const int x, const int y, const std::u32string& str)
  {
    print(x, y, m_defaultStyle, str);
  }
  // Print a formatted string, with specific style
  void Console::print(const int x, const int y, const TextStyle& style, const char* fmt, ...)
  {
    va_list args;
    va_start(args, fmt);
    int size = _computeStringSize(fmt, args);
    va_end(args);
    va_start(args, fmt);
    std::string str = _computeString(size, fmt, args);
    va_end(args);
    print(x, y, style, _stringToU32String(str));
  }
  // Print an utf-8 string, with specific style
  void Console::print(const int x, const int y, const TextStyle& style, const std::string& str)
  {
    if (str.size() > 0)
    {
      print(x, y, style, _stringToU32String(str));
    }
  }
  // Print an utf-32 string, with specific style
  void Console::print(const int x, const int y, const TextStyle& style, const std::u32string& str)
  {
    if (str.size() > 0)
    {
      int xStartPos = 0;
      Alignment align = style.getAlignment();
      if (align == Alignment::CENTER)
      {
        xStartPos = x - (str.size() / 2);
      }
      else if (align == Alignment::RIGHT)
      {
        xStartPos = x - str.size() + 1;
      }
      else
      {
        xStartPos = x;
      }
      for (unsigned i = 0u; i < str.size(); ++i)
      {
        setChar(xStartPos + i, y, str.at(i), style);
      }
    }
  }
  // Print a string with autowrap inside a rectangle
  void Console::printRect(const int x, const int y,
                          const unsigned w, const unsigned h,
                          const bool clearText, const char* fmt, ...)
  {
    va_list args;
    va_start(args, fmt);
    int size = _computeStringSize(fmt, args);
    va_end(args);
    va_start(args, fmt);
    std::string str = _computeString(size, fmt, args);
    va_end(args);
    printRect(x, y, w, h, clearText, m_defaultStyle, _stringToU32String(str));
  }
  // Print an utf-8 string with autowrap inside a rectangle and default style
  void Console::printRect(const int x, const int y,
                          const unsigned w, const unsigned h,
                          const bool clearText, const std::string& str)
  {
    printRect(x, y, w, h, clearText, m_defaultStyle, _stringToU32String(str));
  }
  // Print an utf-32 string with autowrap inside a rectangle and default style
  void Console::printRect(const int x, const int y,
                          const unsigned w, const unsigned h,
                          const bool clearText, const std::u32string& str)
  {
    printRect(x, y, w, h, clearText, m_defaultStyle, str);
  }
  // Print a string with autowrap inside a rectangle and specific style
  void Console::printRect(const int x, const int y,
                          const unsigned w, const unsigned h,
                          const bool clearText, const TextStyle& style, const char* fmt, ...)
  {
    va_list args;
    va_start(args, fmt);
    int size = _computeStringSize(fmt, args);
    va_end(args);
    va_start(args, fmt);
    std::string str = _computeString(size, fmt, args);
    va_end(args);
    printRect(x, y, w, h, clearText, style, _stringToU32String(str));
  }
   // Print an utf-8 string with autowrap inside a rectangle and specific style
  void Console::printRect(const int x, const int y,
                          const unsigned w, const unsigned h,
                          const bool clearText, const TextStyle& style, const std::string& str)
  {
    printRect(x, y, w, h, clearText, style, _stringToU32String(str));
  }
  // Print an utf-32 string with autowrap inside a rectangle and specific style
  void Console::printRect(const int x, const int y,
                          const unsigned w, const unsigned h,
                          const bool clearText, const TextStyle& style, const std::u32string& str)
  {
    // Compute the lines
    std::vector<std::u32string> split = _splitRect(w, str);
    // Compute the reference position according to the alignment
    int xPos = x;
    Alignment align = style.getAlignment();
    if (align == Alignment::CENTER)
    {
      xPos = x + (w / 2);
    }
    else if (align == Alignment::RIGHT)
    {
      xPos = x + w - 1;
    }
    else
    {
      xPos = x;
    }
    // Change the style for the whole rect before printing
    rect(x, y, w, h, clearText, style);
    // Background is already set, no need to set again
    TextStyle txtStyle = style;
    txtStyle.setBackgroundFlag(BackgroundFlag::NONE);
    // Print the strings
    for (unsigned i = 0u; (i < split.size()) && (i < h); ++i)
    {
      print(xPos, y + i, txtStyle, split.at(i));
    }
  }
  // Get the number of lines for an autowrapped text
  unsigned Console::getHeightRect(const unsigned w, const char* fmt, ...)
  {
    va_list args;
    va_start(args, fmt);
    int size = _computeStringSize(fmt, args);
    va_end(args);
    va_start(args, fmt);
    std::string str = _computeString(size, fmt, args);
    va_end(args);
    return getHeightRect(w, _stringToU32String(str));
  }
  unsigned Console::getHeightRect(const unsigned w, const std::string& str)
  {
    return getHeightRect(w, _stringToU32String(str));
  }
  unsigned Console::getHeightRect(const unsigned w, const std::u32string& str)
  {
    return _splitRect(w, str).size();
  }

  // Fill a rectangle with the defaut style
  void Console::rect(const int x, const int y, const unsigned w, const unsigned h,
                     const bool clearText)
  {
    rect(x, y, w, h, clearText, m_defaultStyle);
  }
  // Fill a rectangle with the given style
  void Console::rect(const int x, const int y, const unsigned w, const unsigned h,
                     const bool clearText, const TextStyle& style)
  {
    for (unsigned j = 0; j < h; ++j)
    {
      for (unsigned i = 0; i < w; ++i)
      {
        char32_t codePoint = getChar(x + i, y + j);
        if (clearText)
        {
          codePoint = 0u;
        }
        setChar(x + i, y + j, codePoint, style);
      }
    }
  }
  // Draw an horizontal line: fill a line with the codepoint for an horizontal line
  void Console::hline(const int x, const int y, const unsigned l)
  {
    hline(x, y, l, m_defaultStyle);
  }
  void Console::hline(const int x, const int y, const unsigned l, const TextStyle& style)
  {
    for (unsigned i = 0; i < l; ++i)
    {
      setChar(x + i, y, style.getBoxDrawingCharacter(BoxDrawing::HORIZONTAL), style);
    }
  }
  // Draw a vertical line: fill a line with the codepoint for a vertical line
  void Console::vline(const int x, const int y, const unsigned l)
  {
    vline(x, y, l, m_defaultStyle);
  }
  void Console::vline(const int x, const int y, const unsigned l, const TextStyle& style)
  {
    for (unsigned i = 0; i < l; ++i)
    {
      setChar(x, y + i, style.getBoxDrawingCharacter(BoxDrawing::VERTICAL), style);
    }
  }
  // Draw a window frame, with an optional title
    void Console::printFrame(const int x, const int y, const unsigned w, const unsigned h,
                             const bool clearText)
  {
    printFrame(x, y, w, h, clearText, m_defaultStyle, U"");
  }
  void Console::printFrame(const int x, const int y, const unsigned w, const unsigned h,
                           const bool clearText, const char* fmt, ...)
  {
    std::string title;
    va_list args;
    va_start(args, fmt);
    int size = _computeStringSize(fmt, args);
    va_end(args);
    va_start(args, fmt);
    title = _computeString(size, fmt, args);
    va_end(args);
    printFrame(x, y, w, h, clearText, m_defaultStyle, _stringToU32String(title));
  }
  void Console::printFrame(const int x, const int y, const unsigned w, const unsigned h,
                           const bool clearText, const std::string& title)
  {
    printFrame(x, y, w, h, clearText, m_defaultStyle, _stringToU32String(title));
  }
  void Console::printFrame(const int x, const int y, const unsigned w, const unsigned h,
                           const bool clearText, const std::u32string& title)
  {
    printFrame(x, y, w, h, clearText, m_defaultStyle, title);
  }
  //
  void Console::printFrame(const int x, const int y, const unsigned w, const unsigned h,
                           const bool clearText, const TextStyle& style)
  {
    printFrame(x, y, w, h, clearText, style, U"");
  }
  void Console::printFrame(const int x, const int y, const unsigned w, const unsigned h,
                           const bool clearText, const TextStyle& style,
                           const char* fmt, ...)
  {
    std::string title;
    va_list args;
    va_start(args, fmt);
    int size = _computeStringSize(fmt, args);
    va_end(args);
    va_start(args, fmt);
    title = _computeString(size, fmt, args);
    va_end(args);
    printFrame(x, y, w, h, clearText, style, _stringToU32String(title));
  }
  //
  void Console::printFrame(const int x, const int y, const unsigned w, const unsigned h,
                           const bool clearText, const TextStyle& style,
                           const std::string& title)
  {
    printFrame(x, y, w, h, clearText, style, _stringToU32String(title));
  }
  //
  void Console::printFrame(const int x, const int y, const unsigned w, const unsigned h,
                           const bool clearText, const TextStyle& style,
                           const std::u32string& title)
  {
    // A frame is at least 2 in width and 2 in height
    if ((w > 1u) && (h > 1u))
    {
      // Inner part
      rect(x + 1u, y + 1u, w - 2u, h - 2u, clearText, style);
      // Borders
      // Top bar
      hline(x + 1u, y, w - 2u, style);
      // Bottom bar
      hline(x + 1u, y + h - 1u, w - 2u, style);
      // Left bar
      vline(x, y + 1u, h - 2u, style);
      // Right bar
      vline(x + w - 1u, y + 1u, h - 2u, style);
      // Corners
      // Top Left
      setChar(x, y, style.getBoxDrawingCharacter(BoxDrawing::DOWN_AND_RIGHT), style);
      // Top Right
      setChar(x + w - 1u, y, style.getBoxDrawingCharacter(BoxDrawing::DOWN_AND_LEFT), style);
      // Bottom Left
      setChar(x, y + h - 1u, style.getBoxDrawingCharacter(BoxDrawing::UP_AND_RIGHT), style);
      // Bottom Right
      setChar(x + w - 1u, y + h - 1u, style.getBoxDrawingCharacter(BoxDrawing::UP_AND_LEFT), style);
      // Title
      if (title != U"")
      {
        TextStyle txtStyle = style;
        txtStyle.setBackgroundFlag(BackgroundFlag::NONE);
        printRect(x + 1u, y, w - 2u, 1u, clearText, txtStyle, title);
      }
    }
  }

  // Getters
  // Width of console
  unsigned Console::getWidth(void) const
  {
    return m_width;
  }
  // Height of console
  unsigned Console::getHeight(void) const
  {
    return m_height;
  }

  // Get default style
  const TextStyle& Console::getDefaultStyle(void) const
  {
    return m_defaultStyle;
  }
  // Default background
  const Color& Console::getDefaultBackground(void) const
  {
    return m_defaultStyle.getBackground();
  }
  // Default foreground
  const Color& Console::getDefaultForeground(void) const
  {
    return m_defaultStyle.getForeground();
  }
  // Default background flag
  BackgroundFlag Console::getBackgroundFlag() const
  {
    return m_defaultStyle.getBackgroundFlag();
  }
  // Default alignment
  Alignment Console::getAlignment() const
  {
    return m_defaultStyle.getAlignment();
  }
  // Default font
  Font Console::getDefaultFont() const
  {
    return m_defaultStyle.getFont();
  }

  // Code point of a cell
  char32_t Console::getChar(const int x, const int y) const
  {
    return m_cells[_cellIndex(x, y)].getCodePoint();
  }
  // Get the style of a cell
  // Note: values from the default style are used when they aren't present at cell level
  TextStyle Console::getStyle(const int x, const int y) const
  {
    TextStyle ret = m_defaultStyle;
    if (_isInside(x, y))
    {
      ret.setForeground(getForeground(x, y));
      ret.setBackground(getBackground(x, y));
      ret.setFont(getFont(x, y));
    }
    return ret;
  }
  // Background of a cell
  const Color& Console::getBackground(const int x, const int y) const
  {
    return m_cells[_cellIndex(x, y)].getBackground();
  }
  // Foreground of a cell
  const Color& Console::getForeground(const int x, const int y) const
  {
    return m_cells[_cellIndex(x, y)].getForeground();
  }
  // Font of a cell
  Font Console::getFont(const int x, const int y) const
  {
    return m_cells[_cellIndex(x, y)].getFont();
  }

  // Blitting
  // blit console on another
  void Console::blit(const Console& src, const int xSrc, const int ySrc, const int wSrc, const int hSrc,
                     Console& dst, const int xDst, const int yDst,
                     const float foregroundAlpha, const float backgroundAlpha)
  {
    // The alpha levels must be between 0.0 and 1.0
    // At least one of the alpha levels should be non-zero, or else the source is transparent
    if ( (foregroundAlpha >= 0.0f) && (backgroundAlpha >= 0.0f)
      && (foregroundAlpha <= 1.0f) && (backgroundAlpha <= 1.0f)
      && ((foregroundAlpha > 0.0f) || (backgroundAlpha > 0.0f)))
    {
      for (int j = 0; j < hSrc; ++j)
      {
        for (int i = 0; i < wSrc; ++i)
        {
          const int xPosSrc = xSrc + i;
          const int yPosSrc = ySrc + j;
          const int xPosDst = xDst + i;
          const int yPosDst = yDst + j;
          // Only blit the area inside both consoles and the area should be blit
          if ( src._isInside(xPosSrc, yPosSrc)
            && dst._isInside(xPosDst, yPosDst)
            && (   !src.m_isIgnoreCellColorEnabled
                || (src.getBackground(xPosSrc, yPosSrc) != src.m_ignoreCellColor)))
          {
            // The foreground color and char depends on wether the area are blank or not
            const ConsoleCell& srcCell = src.m_cells.at(src._cellIndex(xPosSrc, yPosSrc));
            const ConsoleCell& dstCell = dst.m_cells.at(dst._cellIndex(xPosDst, yPosDst));
            //
            // CodePoint to set
            char32_t codePoint = dstCell.getCodePoint();
            // Style to set
            TextStyle style = dst.getStyle(xPosDst, yPosDst);
            style.setBackgroundFlag(BackgroundFlag::SET);
            // Background
            style.setBackground(
              Color::lerp(dstCell.getBackground(), srcCell.getBackground(), backgroundAlpha)
            );
            //
            // The effect applied for the foreground and the codePoint to display
            // depends on several parameters
            // Based on the LibTCOD implementation of console blitting
            if (srcCell.isBlank())
            {
              style.setForeground(
                Color::lerp(dstCell.getForeground(), srcCell.getBackground(), backgroundAlpha)
              );
            }
            else if (dstCell.isBlank())
            {
              codePoint = srcCell.getCodePoint();
              style.setFont(srcCell.getFont());
              style.setForeground(
                Color::lerp(dstCell.getBackground(), srcCell.getForeground(), foregroundAlpha)
              );
            }
            else if (dstCell.getCodePoint() == srcCell.getCodePoint())
            {
              style.setForeground(
                Color::lerp(dstCell.getForeground(), srcCell.getForeground(), foregroundAlpha)
              );
            }
            else if (foregroundAlpha < 0.5f)
            {
              style.setForeground(
                Color::lerp(dstCell.getForeground(), dstCell.getForeground(), 2.0f * foregroundAlpha)
              );
            }
            else
            {
              codePoint = srcCell.getCodePoint();
              style.setFont(srcCell.getFont());
              style.setForeground(
                Color::lerp(dstCell.getBackground(), srcCell.getForeground(), 2.0f * (foregroundAlpha - 0.5f))
              );
            }
            // Update the char
            dst.setChar(xPosDst, yPosDst, codePoint, style);
          }
        }
      }
    }
  }
  // Transparent color when bliting: cells with background set to the key color are not blit
  void Console::setIgnoreCellColor(const Color& col)
  {
    m_isIgnoreCellColorEnabled = true;
    m_ignoreCellColor = col;
  }
  // Reset (disable) the key color
  void Console::resetIgnoreCellColor()
  {
    m_isIgnoreCellColorEnabled = false;
  }

  bool Console::_isDirty(const int x, const int y) const
  {
    return m_cells[_cellIndex(x, y)].isDirty();
  }

  void Console::_unsetDirty(const int x, const int y)
  {
    m_cells[_cellIndex(x, y)].unsetDirty();
  }

  bool Console::_isInside(const int x, const int y) const
  {
    return ((x >= 0) && (x < static_cast<int>(m_width)) && (y >= 0) && (y < static_cast<int>(m_height)));
  }

  int Console::_cellIndex(const int x, const int y) const
  {
    return x + (y * m_width);
  }

  int Console::_computeStringSize(const char* fmt, va_list args)
  {
    return vsnprintf(NULL, 0u, fmt, args);
  }

  std::string Console::_computeString(int stringSize, const char* fmt, va_list args)
  {
    std::string ret;
    if (stringSize >= 0)
    {
      char* buff = new char[stringSize + 1];
      (void)vsnprintf(buff, stringSize + 1, fmt, args);
      ret = buff;
      delete[] buff;
    }
    return ret;
  }

  std::u32string Console::_stringToU32String(const std::string str)
  {
    // Convert from utf-8 char* to utf-32 char32_t* in order to update the console cells
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> u32conv;
    return u32conv.from_bytes(str);
  }

  std::vector<std::u32string> Console::_splitRect(const unsigned w, const std::u32string& str)
  {
    std::vector<std::u32string> ret;
    // Split the string along the spaces
    unsigned startingPos = 0u;
    unsigned nextSpace = 0u;
    std::u32string currentLine;
    bool firstWord = true;
    while (startingPos < str.size())
    {
      nextSpace = str.find(U' ', startingPos);
      std::u32string word = str.substr(startingPos, nextSpace - startingPos);
      // Check if we can add the word to the current line
      if ((currentLine.size() + 1u + word.size()) < w)
      {
        if (firstWord)
        {
          currentLine.append(word);
          firstWord = false;
        }
        else
        {
          currentLine.append(1, U' ').append(word);
        }
      }
      else
      {
        // We can't append the word to the current line,
        // Add the current line to the line list and initialize the next line with the word
        ret.push_back(currentLine);
        currentLine = word;
      }
      // compute the next starting position
      if (nextSpace >= str.size())
      {
        // No next space, end the loop and add the current line to the line list
        startingPos = str.size();
        ret.push_back(currentLine);
      }
      else
      {
        startingPos = nextSpace + 1u;
      }

    }
    return ret;
  }

}

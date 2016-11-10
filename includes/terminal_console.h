
#ifndef _TERMINAL_CONSOLE__H_
#define _TERMINAL_CONSOLE__H_

#include "terminal_color.h"
#include "terminal_textstyle.h"
#include <string>
#include <cstdarg>

namespace LRTerminal
{
  // Note: The console class is somewhat based on the libtcod interface, but they are some differences
  // This class represents an offscreen console that can be blitted on other offscreen consoles
  // or the root console.
  class Console
  {
  public:
    // Constructor, destructor
    Console(const unsigned width, const unsigned height);
    virtual ~Console();

    // Set default styles
    void setDefaultStyle(const TextStyle& style);
    // Default colors when cleared
    void setDefaultBackground(const Color& col);
    void setDefaultForeground(const Color& col);
    // Set the default background flag
    void setBackgroundFlag(const BackgroundFlag flag);
    // Set the default text alignment
    void setAlignment(const Alignment align);
    // Set the default font
    void setDefaultFont(const Font font);

    // Clear the console: set all characters to nul and the colors to the default colors
    void clear(void);

    // Set the codepoint of a cell
    void setChar(const int x, const int y, const char32_t c);
    // Set all the properties of a cell from a style
    void setChar(const int x, const int y, const char32_t c, const TextStyle& style);
    // Set the style of a char
    void setStyle(const int x, const int y, const TextStyle& style);
    // Set the background color of a cell
    void setBackground(const int x, const int y, const Color& col,
                           const BackgroundFlag flag = BackgroundFlag::SET);
    // Set the foreground color of a cell
    void setForeground(const int x, const int y, const Color& col);
    // Set the font variant of a cell
    void setFont(const int x, const int y, const Font font);

    // Print a formatted string with default style
    void print(const int x, const int y, const char* fmt, ...);
    // Print an utf-8 string with default style
    void print(const int x, const int y, const std::string& str);
    // Print an utf-32 string with default style
    void print(const int x, const int y, const std::u32string& str);
    // Print a formatted string, with specific style
    void print(const int x, const int y, const TextStyle& style, const char* fmt, ...);
    // Print an utf-8 string, with specific style
    void print(const int x, const int y, const TextStyle& style, const std::string& str);
    // Print an utf-32 string, with specific style
    void print(const int x, const int y, const TextStyle& style, const std::u32string& str);

    // Print a string with autowrap inside a rectangle
    void printRect(const int x, const int y,
                   const unsigned w, const unsigned h,
                   const bool clearText, const char* fmt, ...);
    // Print an utf-8 string with autowrap inside a rectangle and default style
    void printRect(const int x, const int y,
                   const unsigned w, const unsigned h,
                   const bool clearText, const std::string& str);
    // Print an utf-32 string with autowrap inside a rectangle and default style
    void printRect(const int x, const int y,
                   const unsigned w, const unsigned h,
                   const bool clearText, const std::u32string& str);
    // Print a string with autowrap inside a rectangle and specific style
    void printRect(const int x, const int y,
                   const unsigned w, const unsigned h,
                   const bool clearText, const TextStyle& style, const char* fmt, ...);
    // Print an utf-8 string with autowrap inside a rectangle and specific style
    void printRect(const int x, const int y,
                   const unsigned w, const unsigned h,
                   const bool clearText, const TextStyle& style, const std::string& str);
    // Print an utf-32 string with autowrap inside a rectangle and specific style
    void printRect(const int x, const int y,
                   const unsigned w, const unsigned h,
                   const bool clearText, const TextStyle& style, const std::u32string& str);
    // Get the number of lines for an autowrapped text
    unsigned getHeightRect(const unsigned w, const char* fmt, ...);
    unsigned getHeightRect(const unsigned w, const std::string& str);
    unsigned getHeightRect(const unsigned w, const std::u32string& str);

    // TODO: style control ?

    // Fill a rectangle with the default style
    void rect(const int x, const int y, const unsigned w, const unsigned h,
              const bool clearText);
    // Fill a rectangle with the given style
    void rect(const int x, const int y, const unsigned w, const unsigned h,
              const bool clearText, const TextStyle& style);
    // Draw an horizontal line: fill a line with the codepoint for an horizontal line
    void hline(const int x, const int y, const unsigned l);
    void hline(const int x, const int y, const unsigned l, const TextStyle& style);
    // Draw a vertical line: fill a line with the codepoint for a vertical line
    void vline(const int x, const int y, const unsigned l);
    void vline(const int x, const int y, const unsigned l, const TextStyle& style);
    // Draw a window frame, with an optional title
    // Default style
    void printFrame(const int x, const int y, const unsigned w, const unsigned h,
                    const bool clearText);
    void printFrame(const int x, const int y, const unsigned w, const unsigned h,
                    const bool clearText, const char* fmt, ...);
    void printFrame(const int x, const int y, const unsigned w, const unsigned h,
                    const bool clearText, const std::string& title);
    void printFrame(const int x, const int y, const unsigned w, const unsigned h,
                    const bool clearText, const std::u32string& title);
    // Specific style
    void printFrame(const int x, const int y, const unsigned w, const unsigned h,
                    const bool clearText, const TextStyle& style);
    void printFrame(const int x, const int y, const unsigned w, const unsigned h,
                    const bool clearText, const TextStyle& style,
                    const char* fmt, ...);
    void printFrame(const int x, const int y, const unsigned w, const unsigned h,
                    const bool clearText, const TextStyle& style,
                    const std::string& title);
    void printFrame(const int x, const int y, const unsigned w, const unsigned h,
                    const bool clearText, const TextStyle& style,
                    const std::u32string& title);

    // Getters
    // Width of console
    unsigned getWidth(void) const;
    // Height of console
    unsigned getHeight(void) const;

    // Default style
    const TextStyle& getDefaultStyle(void) const;
    // Default background
    const Color& getDefaultBackground(void) const;
    // Default foreground
    const Color& getDefaultForeground(void) const;
    // Default background flag
    BackgroundFlag getBackgroundFlag() const;
    // Default alignment
    Alignment getAlignment() const;
    // Default font
    Font getDefaultFont() const;

    // Code point of a cell
    char32_t getChar(const int x, const int y) const;
    // Get the style of a cell
    // Note: values from the default style are used when they aren't present at cell level
    TextStyle getStyle(const int x, const int y) const;
    // Background of a cell
    const Color& getBackground(const int x, const int y) const;
    // Foreground of a cell
    const Color& getForeground(const int x, const int y) const;
    // Font of a cell
    Font getFont(const int x, const int y) const;

    // Blitting
    // blit console on another
    static void blit(const Console& src, const int xSrc, const int ySrc, const int wSrc, const int hSrc,
                     Console& dst, const int xDst, const int yDst,
                     const float foregroundAlpha = 1.0, const float backgroundAlpha = 1.0);
    // Color to ignore cell when bliting: cells with background set to that color are not blit
    void setIgnoreCellColor(const Color& col);
    // Reset (disable) the ignore cell color
    void resetIgnoreCellColor();

  protected:
    // For use when rendering the console
    bool _isDirty(const int x, const int y) const;
    void _unsetDirty(const int x, const int y);

  private:
    // Class representing a cell of the console
    class ConsoleCell
    {
    public:
      ConsoleCell();
      const Color& getBackground(void) const;
      const Color& getForeground(void) const;
      char32_t getCodePoint(void) const;
      Font getFont(void) const;
      bool isDirty(void) const;
      bool isBlank(void) const;

      void setForeground(const Color& color);
      void setBackground(const Color& color, const BackgroundFlag flag = BackgroundFlag::SET);
      void setCodePoint(const char32_t codePoint);
      void setFont(const Font font);

      void unsetDirty(void);

    private:
      Color m_background; // Background color of the cell
      Color m_foreground; // Foreground color of the cell
      char32_t m_codePoint; // Codepoint of the character of the cell
      Font m_font; // Font in which the character should be rendered
      bool m_isDirty; // Flag to tell if the cell should be redrawn
    };

    bool _isInside(const int x, const int y) const;
    int _cellIndex(const int x, const int y) const;
    // Get the expected size of a formatted string
    static int _computeStringSize(const char* fmt, va_list args);
    // Compute a formatted string
    static std::string _computeString(int stringSize, const char* fmt, va_list args);
    // Convert a utf8 string into a utf-32 string, suitable for filling the console
    static std::u32string _stringToU32String(const std::string str);
    // Split a string into lines according to a given width
    static std::vector<std::u32string> _splitRect(const unsigned w, const std::u32string& str);

    std::vector<ConsoleCell> m_cells; // Cells of the console, size = width * height
    unsigned m_width; // Width of the console
    unsigned m_height; // Height of the console
    TextStyle m_defaultStyle; // Default text style
    bool m_isIgnoreCellColorEnabled; // By default, ignored cells feature is disabled when blitting
    Color m_ignoreCellColor; // Background color for indicating ignored cells when blitting
  };

}

#endif

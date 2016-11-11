
#ifndef _TERMINAL_TEXTSTYLE__H_
#define _TERMINAL_TEXTSTYLE__H_

#include "terminal_color.h"

namespace LRTerminal
{
  // Built-in fonts available when printing text
  // The CUSTOM font is available for user-defined glyphs
  enum class Font
  {
    DEFAULT,
    TAMSYN_REGULAR,
    TAMSYN_BOLD,
    SONY_MISC_8x16,
    MISC_MISC_8x13,
    MISC_MISC_8x13_BOLD,
    MISC_MISC_8x13_OBLIQUE,
    TERMINUS,
    TERMINUS_BOLD,
    CUSTOM,
  };

  // Flags used when changing the background color of a console cell
  // The indicated operations are done component by component (values between 0 and 1)
  enum class BackgroundFlag
  {
    NONE, // The cell color is not changed: cellbk = cellbk
    SET, // The cell color is replaced by the set color: cellbk = newbk
    MULTIPLY, // The cell color is multiplied by the set color: cellbk = cellbk * newbk
    LIGHTEN, // cellbk = MAX(cellbk, newbk)
    DARKEN, // cellbk = MIN(cellbk, newbk)
    SCREEN, // Inverse of multiply: (1-cellbk) = (1-cellbk)*(1-newbk)
    COLOR_DODGE, // cellbk = newbk / (1-cellbk)
    COLOR_BURN, // cellbk = 1 - (1-cellbk)/newbk
    ADD, // cellbk = cellbk + newbk
    BURN, // cellbk = cellbk + newbk - 1
    OVERLAY, // cellbk = (newbk < 0.5) ? (2*cellbk*newbk) : (1 - 2*(1-cellbk)*(1-newbk))
    //ADDALPHA and ALPHA are currently not supported (they need an additionnal parameter)
  };

  // Text alignment when printing
  enum class Alignment
  {
    LEFT,
    CENTER,
    RIGHT,
  };

    // style of the box drawing lines used when using the functions vline, hline and printFrame
  enum class LineThickness
  {
    LIGHT, // ─
    HEAVY, // ━
    DOUBLE, // ═
  };

  // Named positions
  enum class BoxDrawing
  {
    HORIZONTAL, // ─
    VERTICAL, // │
    DOWN_AND_RIGHT, // ┌
    DOWN_AND_LEFT, // ┐
    UP_AND_RIGHT, // └
    UP_AND_LEFT, // ┘
    VERTICAL_AND_RIGHT, // ├
    VERTICAL_AND_LEFT, // ┤
    DOWN_AND_HORIZONTAL, // ┬
    UP_AND_HORIZONTAL, // ┴
    VERTICAL_AND_HORIZONTAL, // ┼
  };

  // Styles to use when printing text
  class TextStyle
  {
  public:
    TextStyle();
    TextStyle(const TextStyle& that);
    TextStyle& operator=(const TextStyle& that);
    // Setters
    void setBackground(const Color& col);
    void setForeground(const Color& col);
    void setFont(const Font font);
    void setBackgroundFlag(const BackgroundFlag flag);
    void setAlignment(const Alignment align);
    void setLineThickness(const LineThickness thickness);
    // Getters
    const Color& getBackground(void) const;
    const Color& getForeground(void) const;
    Font getFont(void) const;
    BackgroundFlag getBackgroundFlag(void) const;
    Alignment getAlignment(void) const;
    LineThickness getLineThickness(void) const;

    // For printing box-drawing characters using the current style
    char32_t getBoxDrawingCharacter(const BoxDrawing boxDrawing) const;

  private:
    Color m_background;
    Color m_foreground;
    Font m_font;
    BackgroundFlag m_backgroundFlag;
    Alignment m_alignment;
    LineThickness m_lineThickness;
  };

}


#endif

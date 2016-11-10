
#ifndef _TERMINAL_FONTDATA__H_
#define _TERMINAL_FONTDATA__H_

#include "terminal_glyphs.h"
#include <map>

namespace LRTerminal
{
  // A font is a map of glyphs
  class FontData
  {
  public:
    // Constructor & destructor
    FontData(unsigned glyphWidth, unsigned glyphHeight);
    ~FontData(void);
    // Add a glyph at a code point
    void addGlyph(char32_t codePoint,
                  const uint8_t* const srcImage,
                  unsigned srcWidth, unsigned srcHeight,
                  unsigned srcX, unsigned srcY);
    // Add all glyphs from an image
    void addGlyphs(char32_t codePointStart,
                   const uint8_t* const srcImage,
                   unsigned srcWidth, unsigned srcHeight);
    // Get a glyph from a codePoint
    const Glyph& getGlyph(char32_t codePoint) const;
    // Get the character sizes of the font
    unsigned getGlyphWidth() const;
    unsigned getGlyphHeight() const;
    // Check if a font have a glyph at given code point
    bool hasGlyph(char32_t codePoint) const;
  private:
    bool _checkIsBlank(const uint8_t* const srcImage,
                       unsigned srcWidth, unsigned srcHeight,
                       unsigned srcX, unsigned srcY) const;
    unsigned m_glyphWidth;
    unsigned m_glyphHeight;
    std::map<char32_t, Glyph> m_glyphMap;
  };

}

#endif

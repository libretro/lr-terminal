
#ifndef _TERMINAL_BUILTIN_FONTS__H_
#define _TERMINAL_BUILTIN_FONTS__H_

#include "terminal_fontdata.h"
#include "terminal_textstyle.h"
#include <map>

namespace LRTerminal
{
  class Glyph;

  // Font sizes
  const unsigned C_GLYPH_WIDTH(8u);
  const unsigned C_GLYPH_HEIGHT(16u);

  // The builtin fonts class is a singleton
  // Outside the loading functions,
  class BuiltinFonts
  {
  public:
    // Constructor
    BuiltinFonts();
    // Destructor
    ~BuiltinFonts();
    //
    const FontData& getFontData(const Font font) const;
    const Glyph& getGlyph(const Font font, const char32_t codePoint) const;

    // Load an XBM image as part of a font, used for initializing the builtin fonts data
    void loadXbmFont(const Font font, const char32_t startingCodePoint,
                     const unsigned width, const unsigned height,
                     const unsigned char* const xbmImage);

    // TODO: Load an XPM image

    // Add glyphs to the custom font. The custom font has initially no glyphs
    // The image in parameter represents the alpha mask of the glyphs
    // Each char corresponds to the opacity level of a pixel, 0x00 is transparent, 0xFF is opaque
    void addToCustomFont(const char32_t startingCodePoint,
                         const unsigned width, const unsigned height,
                         const unsigned char* const image);
    // Add glyphs to he custom font. The glyphs are formatted in a monochrome XBM image
    void addXBMToCustomFont(const char32_t startingCodePoint,
                            const unsigned width, const unsigned height,
                            const unsigned char* const image);

  private:
    // Map Font <-> FontData
    std::map<Font, FontData> m_fonts;
  };

}

#endif

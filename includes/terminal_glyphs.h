
#ifndef _TERMINAL_GLYPHS__H_
#define _TERMINAL_GLYPHS__H_

#include <cstdint>

namespace LRTerminal
{
  // Base class for the font
  // Each glyph represents a character
  class Glyph
  {
  public:
    // Constructor
     // Blank glyph
    Glyph(unsigned width, unsigned height);
     // Glyph from a source image, scrX and scrY are the position in pixels of the glyph in the source image
    Glyph(unsigned width, unsigned height,
          const uint8_t* const srcImage,
          unsigned srcWidth, unsigned srcHeight, unsigned srcX, unsigned srcY);
    // Destructor
    ~Glyph();

    // Get the data
    unsigned getWidth(void) const;
    unsigned getHeight(void) const;
    const uint8_t* getImage(void) const;
  private:
    unsigned m_width;
    unsigned m_height;
    uint8_t* m_image; // Glyph image as a greyscale image of size width * height, representing an alpha mask
  };
}

#endif

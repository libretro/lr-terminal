#include "terminal_glyphs.h"
#include <cstring>
#include <cstdio>
namespace LRTerminal
{
  // Blank glyph
  Glyph::Glyph(unsigned width, unsigned height): m_width(width), m_height(height)
  {
    m_image = new uint8_t[m_width*m_height];
    memset(m_image, 0u, m_width * m_height);
  }

  // Glyph from a source image, scrX and scrY are the position in pixels of the glyph in the source image
  Glyph::Glyph(unsigned width, unsigned height,
               const uint8_t* const srcImage,
               unsigned srcWidth, unsigned srcHeight, unsigned srcX, unsigned srcY):
      m_width(width), m_height(height)
  {
    m_image = new uint8_t[m_width*m_height];
    for (unsigned i = 0u; i < m_height; ++i)
    {
      memcpy(m_image + (i * m_width), srcImage + ((srcY + i) * srcWidth) + srcX, m_width * sizeof(uint8_t));
    }
  }

  // Destructor
  Glyph::~Glyph()
  {
    delete[] m_image;
  }

  // Getters
  unsigned Glyph::getWidth(void) const
  {
    return m_width;
  }
  unsigned Glyph::getHeight(void) const
  {
    return m_height;
  }
  const uint8_t* Glyph::getImage(void) const
  {
    return m_image;
  }
}

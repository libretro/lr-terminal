#include "terminal_fontdata.h"

namespace LRTerminal
{

  FontData::FontData(unsigned glyphWidth, unsigned glyphHeight):
      m_glyphWidth(glyphWidth), m_glyphHeight(glyphHeight)
  {
    // Add a default blank glyph at code point 0
    m_glyphMap.emplace(std::piecewise_construct,
                       std::forward_as_tuple(0u),
                       std::forward_as_tuple(m_glyphWidth, m_glyphHeight));
  }

  FontData::~FontData()
  {
    m_glyphMap.clear();
  }

  // Add a glyph at a code point
  void FontData::addGlyph(char32_t codePoint,
                          const uint8_t* const srcImage,
                          unsigned srcWidth, unsigned srcHeight, unsigned srcX, unsigned srcY)
  {
    // If the glyph is not nul, erase it
    if (codePoint != 0u)
    {
      m_glyphMap.erase(codePoint);
    }
    // Do not add blank glyphs to the font, as it's the default glyph
    // The code point 0 is reserved as the blank glyph and is added in the constructor
    if ((codePoint != 0u) && (!_checkIsBlank(srcImage, srcWidth, srcHeight, srcX, srcY)))
    {
      m_glyphMap.emplace(std::piecewise_construct,
                         std::forward_as_tuple(codePoint),
                         std::forward_as_tuple(
                           m_glyphWidth, m_glyphHeight,
                           srcImage,
                           srcWidth, srcHeight, srcX, srcY
                        ));
    }
  }

  void FontData::addGlyphs(char32_t codePointStart,
                           const uint8_t* const srcImage,
                           unsigned srcWidth, unsigned srcHeight)
  {
    unsigned nbGlyphsW = srcWidth / m_glyphWidth;
    unsigned nbGlyphsH = srcHeight / m_glyphHeight;
    for (unsigned j = 0; j < nbGlyphsH; ++j)
    {
      for (unsigned i = 0; i < nbGlyphsW; ++i)
      {
        addGlyph(codePointStart + (j * nbGlyphsW) + i,
                 srcImage,
                 srcWidth, srcHeight,
                 i * m_glyphWidth,
                 j * m_glyphHeight);
      }
    }
  }

  bool FontData::_checkIsBlank(const uint8_t* const srcImage,
                               unsigned srcWidth, unsigned srcHeight,
                               unsigned srcX, unsigned srcY) const
  {
    bool isBlank = true;
    for (unsigned j = 0; (j < m_glyphHeight) && isBlank; ++j)
    {
      for (unsigned i = 0; (i < m_glyphWidth) && isBlank; ++i)
      {
        if (srcImage[((j + srcY) * srcWidth) + srcX + i] != 0u)
        {
          isBlank = false;
        }
      }
    }
    return isBlank;
  }

  // Getters
  const Glyph& FontData::getGlyph(char32_t codePoint) const
  {
    auto found = m_glyphMap.find(codePoint);
    // If the glyph is not present, defaults to the blank glyph located at codepoint 0
    if (found == m_glyphMap.end())
    {
      found = m_glyphMap.find(0u);
    }
    return found->second;
  }

  unsigned FontData::getGlyphWidth() const
  {
    return m_glyphWidth;
  }

  unsigned FontData::getGlyphHeight() const
  {
    return m_glyphHeight;
  }

  bool FontData::hasGlyph(char32_t codePoint) const
  {
    auto found = m_glyphMap.find(codePoint);
    return found != m_glyphMap.end();
  }

}

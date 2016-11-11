#include "terminal_builtin_fonts.h"
#include <cstdint>

// The builtin fonts are stored as xbm or xpm(3) files in ressources/fonts.
// The xbm format describes a monochrome image as a static const array of char, in a C-source file format.
// The xpm format describes a color image as various arrays, in a C-source file format.
// Those files are included like any other C/C++ include files.
// As a result, the data of those fonts are included in the produced binaries.

// Default font
namespace LRTerminal
{
  namespace Fonts::Default
  {
#include "fonts/default/font.inc"
  }
  namespace Fonts::TamsynR
  {
#include "fonts/TamsynR/font.inc"
  }
  namespace Fonts::TamsynB
  {
#include "fonts/TamsynB/font.inc"
  }
  namespace Fonts::SonyMisc8x16
  {
#include "fonts/8x16/font.inc"
  }
  namespace Fonts::MiscMisc8x13
  {
#include "fonts/8x13/font.inc"
  }
  namespace Fonts::MiscMisc8x13B
  {
#include "fonts/8x13B/font.inc"
  }
  namespace Fonts::MiscMisc8x13O
  {
#include "fonts/8x13O/font.inc"
  }
  namespace Fonts::Terminus
  {
#include "fonts/Terminus/font.inc"
  }
  namespace Fonts::TerminusBold
  {
#include "fonts/TerminusBold/font.inc"
  }

  // Constuctor
  BuiltinFonts::BuiltinFonts()
  {
    // Load the default font
    m_fonts.emplace(std::piecewise_construct,
                    std::forward_as_tuple(Font::DEFAULT),
                    std::forward_as_tuple(C_GLYPH_WIDTH,
                                          C_GLYPH_HEIGHT));
    Fonts::Default::load(*this);

    // TamsynR
    m_fonts.emplace(std::piecewise_construct,
                    std::forward_as_tuple(Font::TAMSYN_REGULAR),
                    std::forward_as_tuple(C_GLYPH_WIDTH,
                                          C_GLYPH_HEIGHT));
    Fonts::TamsynR::load(*this);

    // TamsynB
    m_fonts.emplace(std::piecewise_construct,
                    std::forward_as_tuple(Font::TAMSYN_BOLD),
                    std::forward_as_tuple(C_GLYPH_WIDTH,
                                          C_GLYPH_HEIGHT));
    Fonts::TamsynB::load(*this);

    // 8x16
    m_fonts.emplace(std::piecewise_construct,
                    std::forward_as_tuple(Font::SONY_MISC_8x16),
                    std::forward_as_tuple(C_GLYPH_WIDTH,
                                          C_GLYPH_HEIGHT));
    Fonts::SonyMisc8x16::load(*this);

    // 8x13
    m_fonts.emplace(std::piecewise_construct,
                    std::forward_as_tuple(Font::MISC_MISC_8x13),
                    std::forward_as_tuple(C_GLYPH_WIDTH,
                                          C_GLYPH_HEIGHT));
    Fonts::MiscMisc8x13::load(*this);

    // 8x13B
    m_fonts.emplace(std::piecewise_construct,
                    std::forward_as_tuple(Font::MISC_MISC_8x13_BOLD),
                    std::forward_as_tuple(C_GLYPH_WIDTH,
                                          C_GLYPH_HEIGHT));
    Fonts::MiscMisc8x13B::load(*this);

    // 8x13O
    m_fonts.emplace(std::piecewise_construct,
                    std::forward_as_tuple(Font::MISC_MISC_8x13_OBLIQUE),
                    std::forward_as_tuple(C_GLYPH_WIDTH,
                                          C_GLYPH_HEIGHT));
    Fonts::MiscMisc8x13O::load(*this);

    // Terminus
    m_fonts.emplace(std::piecewise_construct,
                    std::forward_as_tuple(Font::TERMINUS),
                    std::forward_as_tuple(C_GLYPH_WIDTH,
                                          C_GLYPH_HEIGHT));
    Fonts::Terminus::load(*this);

    // Terminus Bold
    m_fonts.emplace(std::piecewise_construct,
                    std::forward_as_tuple(Font::TERMINUS_BOLD),
                    std::forward_as_tuple(C_GLYPH_WIDTH,
                                          C_GLYPH_HEIGHT));
    Fonts::TerminusBold::load(*this);

    // Custom font, no glyph associated (outside the blank glyph)
    m_fonts.emplace(std::piecewise_construct,
                    std::forward_as_tuple(Font::CUSTOM),
                    std::forward_as_tuple(C_GLYPH_WIDTH,
                                          C_GLYPH_HEIGHT));
  }

  // Destructor
  BuiltinFonts::~BuiltinFonts()
  {
    m_fonts.clear();
  }

  // Get a font
  const FontData& BuiltinFonts::getFontData(const Font font) const
  {
    return m_fonts.at(font);
  }

  const Glyph& BuiltinFonts::getGlyph(const Font font, const char32_t codePoint) const
  {
    const FontData& fontdata = getFontData(font);
    if (fontdata.hasGlyph(codePoint))
    {
      return fontdata.getGlyph(codePoint);
    }
    else
    {
      return getFontData(Font::DEFAULT).getGlyph(codePoint);
    }
  }

  // Load an XBM image as part of a font variant
  void BuiltinFonts::loadXbmFont(const Font font, const char32_t startingCodePoint,
                                 const unsigned imageWidth, const unsigned imageHeight,
                                 const unsigned char* const imageXbm)
  {
    // Decode the XBM image
    uint8_t* imageBuffer = new uint8_t[imageWidth * imageHeight];
    // Each byte of the image represents a block of eight horizontal pixels
    // 0 is white, 1 is black, but for us, it mean: 0 is transparent, 1 is opaque
    // The blocks are zero-padded if the image width is not a multiple of eight
    unsigned pad = 0u;
    if (imageWidth % 8u != 0u)
    {
      pad = 1u;
    }
    unsigned xbmWidth = ((imageWidth / 8u) + pad);
    for (unsigned j = 0u; j < imageHeight; ++j)
    {
      for (unsigned i = 0u; i < xbmWidth; ++i)
      {
        uint8_t codedVal = imageXbm[i + (j * xbmWidth)];
        for (unsigned k = 0u; k < 8u; ++k)
        {
          // Ignore the zero padded values
          if ((k + (i * 8u)) < imageWidth) {
            // Transform the pixel into a alpha mask value
            // The order of the pixels is little endian
            imageBuffer[k + (i * 8u) + (j * imageWidth)] = 0xFF * (0x01 & codedVal);
            codedVal = codedVal >> 1u;
          }
          else
          {
            // Stop iterating on k as we are in the zero padded values
            break;
          }
        }
      }
    }
    // Add the glyphs
    m_fonts.at(font).addGlyphs(startingCodePoint, imageBuffer, imageWidth, imageHeight);
    delete[] imageBuffer;
  }

  void BuiltinFonts::addToCustomFont(const char32_t startingCodePoint,
                                     const unsigned width, const unsigned height,
                                     const unsigned char* const image)
  {
    m_fonts.at(Font::CUSTOM).addGlyphs(startingCodePoint, image, width, height);
  }

  void BuiltinFonts::addXBMToCustomFont(const char32_t startingCodePoint,
                                        const unsigned width, const unsigned height,
                                        const unsigned char* const image)
  {
    loadXbmFont(Font::CUSTOM, startingCodePoint, width, height, image);
  }

}

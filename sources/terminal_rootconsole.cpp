#include "terminal_rootconsole.h"

namespace LRTerminal
{
  // Constructor
  RootConsole::RootConsole(const unsigned width, const unsigned height): Console(width, height)
  {
    m_framebuffer = new uint32_t[width * C_GLYPH_WIDTH * height * C_GLYPH_HEIGHT];
  }

  // Destructor
  RootConsole::~RootConsole()
  {
    delete[] m_framebuffer;
  }

  // Render the console into a buffer and returns the buffer
  // Each unsigned represents a pixel in the XRGB_8888 format
  const uint32_t* RootConsole::renderImage(bool& isUpdated)
  {
    isUpdated = false;
    const unsigned consoleHeight = getHeight();
    const unsigned consoleWidth = getWidth();
    //
    for (unsigned ch = 0u; ch < consoleHeight; ++ch)
    {
      for (unsigned cw = 0u; cw < consoleWidth; ++cw)
      {
        // Only render the cell that have been modified
        if (_isDirty(cw, ch))
        {
          // Draw a cell into the framebuffer
          const Glyph& glyph = m_builtinFonts.getGlyph(getFont(cw, ch), getChar(cw, ch));
          const Color& backColor = getBackground(cw, ch);
          const Color& foreColor = getForeground(cw, ch);
          const unsigned glyphHeight = glyph.getHeight();
          const unsigned glyphWidth = glyph.getWidth();
          const uint8_t* const image = glyph.getImage();
          //
          for (unsigned j = 0u; j < glyphHeight; ++j)
          {
            for (unsigned i = 0u; i < glyphWidth; ++i)
            {
              Color col = Color::lerp(backColor, foreColor,
                                      static_cast<float>(image[i + j * glyphWidth]) / 255.0f);
              unsigned idx = ((ch * glyphHeight + j) * consoleWidth * glyphWidth) + (cw * glyphWidth + i);
              //
              m_framebuffer[idx] = col.toXRGB();
            }
          }
          _unsetDirty(cw, ch);
          isUpdated = true;
        }
      }
    }
    return m_framebuffer;
  }

  // Get Font width & height
  const unsigned RootConsole::getFontWidth(void) const
  {
    return C_GLYPH_WIDTH;
  }

  const unsigned RootConsole::getFontHeight(void) const
  {
    return C_GLYPH_HEIGHT;
  }


  void RootConsole::addToCustomFont(const char32_t startingCodePoint,
                                    const unsigned width, const unsigned height,
                                    const unsigned char* const image)
  {
    m_builtinFonts.addToCustomFont(startingCodePoint, width, height, image);
  }

  void RootConsole::addXBMToCustomFont(const char32_t startingCodePoint,
                                       const unsigned width, const unsigned height,
                                       const unsigned char* const image)
  {
    m_builtinFonts.addXBMToCustomFont(startingCodePoint, width, height, image);
  }

}

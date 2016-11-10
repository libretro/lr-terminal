
#ifndef _TERMINAL_ROOTCONSOLE__H_
#define _TERMINAL_ROOTCONSOLE__H_

#include "terminal_console.h"
#include "terminal_builtin_fonts.h"

namespace LRTerminal
{

  // This class represents the Console that is output on screen
  class RootConsole: public Console
  {
  public:
    // Constructors, destructors
    RootConsole(const unsigned width, const unsigned height);
    virtual ~RootConsole();

    // Render the console into a buffer and returns the buffer
    // Each unsigned represents a pixel in the XRGB_8888 format
    // isUpdated is set to true if the image has been updated since last call, false otherwise
    const uint32_t* renderImage(bool& isUpdate);

    // Get Font width & height
    const unsigned getFontWidth(void) const;
    const unsigned getFontHeight(void) const;

    // Custom font
    void addToCustomFont(const char32_t startingCodePoint,
                         const unsigned width, const unsigned height,
                         const unsigned char* const image);
    void addXBMToCustomFont(const char32_t startingCodePoint,
                            const unsigned width, const unsigned height,
                            const unsigned char* const image);

  private:
    uint32_t* m_framebuffer; // buffer on which the console is rendered
    BuiltinFonts m_builtinFonts; // The builtin fonts
  };

}

#endif

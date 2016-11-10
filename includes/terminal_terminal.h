
#ifndef _TERMINAL_TERMINAL__H_
#define _TERMINAL_TERMINAL__H_

namespace LRTerminal
{
  // RootConsole buffer, see terminal_console.h
  class Console;

  // Player enum, for input
  // Order is same as expected by libretro
  enum class PlayerInput
  {
    PLAYER_1 = 0,
    PLAYER_2,
    PLAYER_3,
    PLAYER_4
  };

  // Joypad key enum, for input
  // Value is the same as the masks, see the RETRO_DEVICE_ID_JOYPAD_*
  enum class JoypadKeyInput
  {
    B = 0,
    Y,
    SELECT,
    START,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    A,
    X,
    L,
    R,
  };

  // Interface class, all methods are abstract
  class Terminal
  {
  public:
    // Destructor
    virtual ~Terminal();

    // Get the root console, for rendering
    virtual Console& getRootConsole(void) = 0;

    // Input
    // Test if key is down
    virtual bool isKeyDown(PlayerInput player, JoypadKeyInput key) const = 0;
    // Test if key is up
    virtual bool isKeyUp(PlayerInput player, JoypadKeyInput key) const = 0;

    // Request to shutdown
    virtual void shutdown() const = 0;

    // Add glyphs to the custom font (LRTerminal::Font::CUSTOM). The custom font has initially no glyphs
    // The image in parameter represents the alpha mask of the glyphs
    // Each char corresponds to the opacity level of a pixel, 0x00 is transparent, 0xFF is opaque
    virtual void addToCustomFont(const char32_t startingCodePoint,
                                 const unsigned width, const unsigned height,
                                 const unsigned char* const image) = 0;
    // Add glyphs to he custom font. The glyphs are formatted in a monochrome XBM image
    virtual void addXBMToCustomFont(const char32_t startingCodePoint,
                                    const unsigned width, const unsigned height,
                                    const unsigned char* const image) = 0;
  };
}

#endif

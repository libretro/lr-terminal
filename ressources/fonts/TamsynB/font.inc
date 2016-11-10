// Font loading
//
#include "fonts/TamsynB/Tamsyn8x16b.xbm"
//
static void load(BuiltinFonts& builtinFonts)
{
  builtinFonts.loadXbmFont(Font::TAMSYN_BOLD, 0x000000u,
                            Tamsyn8x16b_width,
                            Tamsyn8x16b_height,
                            Tamsyn8x16b_bits);
}

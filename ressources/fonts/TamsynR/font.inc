// Font loading
//
#include "fonts/TamsynR/Tamsyn8x16r.xbm"
//
static void load(BuiltinFonts& builtinFonts)
{
  builtinFonts.loadXbmFont(Font::TAMSYN_REGULAR, 0x000000u,
                            Tamsyn8x16r_width,
                            Tamsyn8x16r_height,
                            Tamsyn8x16r_bits);
}

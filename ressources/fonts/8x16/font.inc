// Font loading
//
#include "fonts/8x16/u000000-u0000FF.xbm"
#include "fonts/8x16/u002200-u0022FF.xbm"
#include "fonts/8x16/u002400-u00243F.xbm"
//
static void load(BuiltinFonts& builtinFonts)
{
  builtinFonts.loadXbmFont(Font::SONY_MISC_8x16, 0x000000u,
                            u000000_u0000FF_width,
                            u000000_u0000FF_height,
                            u000000_u0000FF_bits);
  builtinFonts.loadXbmFont(Font::SONY_MISC_8x16, 0x002200u,
                            u002200_u0022FF_width,
                            u002200_u0022FF_height,
                            u002200_u0022FF_bits);
  builtinFonts.loadXbmFont(Font::SONY_MISC_8x16, 0x002400u,
                            u002400_u00243F_width,
                            u002400_u00243F_height,
                            u002400_u00243F_bits);
}

// Font loading
//
#include "fonts/8x13O/u000000-u0000FF.xbm"
#include "fonts/8x13O/u000100-u0001FF.xbm"
#include "fonts/8x13O/u000200-u0002FF.xbm"
#include "fonts/8x13O/u000300-u0003FF.xbm"
#include "fonts/8x13O/u000400-u0004FF.xbm"
#include "fonts/8x13O/u000E00-u000EFF.xbm"
#include "fonts/8x13O/u001E00-u001EFF.xbm"
#include "fonts/8x13O/u002000-u0020FF.xbm"
#include "fonts/8x13O/u002100-u0021FF.xbm"
#include "fonts/8x13O/u002200-u0022FF.xbm"
#include "fonts/8x13O/u002400-u0024FF.xbm"
#include "fonts/8x13O/u002600-u0026FF.xbm"
#include "fonts/8x13O/u00FB00-u00FBFF.xbm"
#include "fonts/8x13O/u00FF00-u00FFFF.xbm"
//
static void load(BuiltinFonts& builtinFonts)
{
  builtinFonts.loadXbmFont(Font::MISC_MISC_8x13_OBLIQUE, 0x000000u,
                            u000000_u0000FF_width,
                            u000000_u0000FF_height,
                            u000000_u0000FF_bits);
  builtinFonts.loadXbmFont(Font::MISC_MISC_8x13_OBLIQUE, 0x000100u,
                            u000100_u0001FF_width,
                            u000100_u0001FF_height,
                            u000100_u0001FF_bits);
  builtinFonts.loadXbmFont(Font::MISC_MISC_8x13_OBLIQUE, 0x000200u,
                            u000200_u0002FF_width,
                            u000200_u0002FF_height,
                            u000200_u0002FF_bits);
  builtinFonts.loadXbmFont(Font::MISC_MISC_8x13_OBLIQUE, 0x000300u,
                            u000300_u0003FF_width,
                            u000300_u0003FF_height,
                            u000300_u0003FF_bits);
  builtinFonts.loadXbmFont(Font::MISC_MISC_8x13_OBLIQUE, 0x000400u,
                            u000400_u0004FF_width,
                            u000400_u0004FF_height,
                            u000400_u0004FF_bits);
  builtinFonts.loadXbmFont(Font::MISC_MISC_8x13_OBLIQUE, 0x000E00u,
                            u000E00_u000EFF_width,
                            u000E00_u000EFF_height,
                            u000E00_u000EFF_bits);
  builtinFonts.loadXbmFont(Font::MISC_MISC_8x13_OBLIQUE, 0x001E00u,
                            u001E00_u001EFF_width,
                            u001E00_u001EFF_height,
                            u001E00_u001EFF_bits);
  builtinFonts.loadXbmFont(Font::MISC_MISC_8x13_OBLIQUE, 0x002000u,
                            u002000_u0020FF_width,
                            u002000_u0020FF_height,
                            u002000_u0020FF_bits);
  builtinFonts.loadXbmFont(Font::MISC_MISC_8x13_OBLIQUE, 0x002100u,
                            u002100_u0021FF_width,
                            u002100_u0021FF_height,
                            u002100_u0021FF_bits);
  builtinFonts.loadXbmFont(Font::MISC_MISC_8x13_OBLIQUE, 0x002200u,
                            u002200_u0022FF_width,
                            u002200_u0022FF_height,
                            u002200_u0022FF_bits);
  builtinFonts.loadXbmFont(Font::MISC_MISC_8x13_OBLIQUE, 0x002400u,
                            u002400_u0024FF_width,
                            u002400_u0024FF_height,
                            u002400_u0024FF_bits);
  builtinFonts.loadXbmFont(Font::MISC_MISC_8x13_OBLIQUE, 0x002600u,
                            u002600_u0026FF_width,
                            u002600_u0026FF_height,
                            u002600_u0026FF_bits);
  builtinFonts.loadXbmFont(Font::MISC_MISC_8x13_OBLIQUE, 0x00FB00u,
                            u00FB00_u00FBFF_width,
                            u00FB00_u00FBFF_height,
                            u00FB00_u00FBFF_bits);
  builtinFonts.loadXbmFont(Font::MISC_MISC_8x13_OBLIQUE, 0x00FF00u,
                            u00FF00_u00FFFF_width,
                            u00FF00_u00FFFF_height,
                            u00FF00_u00FFFF_bits);
}

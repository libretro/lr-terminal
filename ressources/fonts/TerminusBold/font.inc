// Font loading
//
#include "fonts/TerminusBold/u000000-u0000FF.xbm"
#include "fonts/TerminusBold/u000100-u0001FF.xbm"
#include "fonts/TerminusBold/u000200-u0002FF.xbm"
#include "fonts/TerminusBold/u000300-u0003FF.xbm"
#include "fonts/TerminusBold/u000400-u0004FF.xbm"
#include "fonts/TerminusBold/u001E00-u001EFF.xbm"
#include "fonts/TerminusBold/u002000-u0020FF.xbm"
#include "fonts/TerminusBold/u002100-u0021FF.xbm"
#include "fonts/TerminusBold/u002200-u0022FF.xbm"
#include "fonts/TerminusBold/u002300-u0023FF.xbm"
#include "fonts/TerminusBold/u002400-u0024FF.xbm"
#include "fonts/TerminusBold/u002500-u0025FF.xbm"
#include "fonts/TerminusBold/u002600-u0026FF.xbm"
#include "fonts/TerminusBold/u002700-u0027FF.xbm"
#include "fonts/TerminusBold/u002800-u0028FF.xbm"
#include "fonts/TerminusBold/u00E000-u00E0FF.xbm"
//

static void load(BuiltinFonts& builtinFonts)
{
  builtinFonts.loadXbmFont(Font::TERMINUS_BOLD, 0x000000u,
                            u000000_u0000FF_width,
                            u000000_u0000FF_height,
                            u000000_u0000FF_bits);
  builtinFonts.loadXbmFont(Font::TERMINUS_BOLD, 0x000100u,
                            u000100_u0001FF_width,
                            u000100_u0001FF_height,
                            u000100_u0001FF_bits);
  builtinFonts.loadXbmFont(Font::TERMINUS_BOLD, 0x000200u,
                            u000200_u0002FF_width,
                            u000200_u0002FF_height,
                            u000200_u0002FF_bits);
  builtinFonts.loadXbmFont(Font::TERMINUS_BOLD, 0x000300u,
                            u000300_u0003FF_width,
                            u000300_u0003FF_height,
                            u000300_u0003FF_bits);
  builtinFonts.loadXbmFont(Font::TERMINUS_BOLD, 0x000400u,
                            u000400_u0004FF_width,
                            u000400_u0004FF_height,
                            u000400_u0004FF_bits);
  builtinFonts.loadXbmFont(Font::TERMINUS_BOLD, 0x001E00u,
                            u001E00_u001EFF_width,
                            u001E00_u001EFF_height,
                            u001E00_u001EFF_bits);
  builtinFonts.loadXbmFont(Font::TERMINUS_BOLD, 0x002000u,
                            u002000_u0020FF_width,
                            u002000_u0020FF_height,
                            u002000_u0020FF_bits);
  builtinFonts.loadXbmFont(Font::TERMINUS_BOLD, 0x002100u,
                            u002100_u0021FF_width,
                            u002100_u0021FF_height,
                            u002100_u0021FF_bits);
  builtinFonts.loadXbmFont(Font::TERMINUS_BOLD, 0x002200u,
                            u002200_u0022FF_width,
                            u002200_u0022FF_height,
                            u002200_u0022FF_bits);
  builtinFonts.loadXbmFont(Font::TERMINUS_BOLD, 0x002300u,
                            u002300_u0023FF_width,
                            u002300_u0023FF_height,
                            u002300_u0023FF_bits);
  builtinFonts.loadXbmFont(Font::TERMINUS_BOLD, 0x002400u,
                            u002400_u0024FF_width,
                            u002400_u0024FF_height,
                            u002400_u0024FF_bits);
  builtinFonts.loadXbmFont(Font::TERMINUS_BOLD, 0x002500u,
                            u002500_u0025FF_width,
                            u002500_u0025FF_height,
                            u002500_u0025FF_bits);
  builtinFonts.loadXbmFont(Font::TERMINUS_BOLD, 0x002600u,
                            u002600_u0026FF_width,
                            u002600_u0026FF_height,
                            u002600_u0026FF_bits);
  builtinFonts.loadXbmFont(Font::TERMINUS_BOLD, 0x002700u,
                            u002700_u0027FF_width,
                            u002700_u0027FF_height,
                            u002700_u0027FF_bits);
  builtinFonts.loadXbmFont(Font::TERMINUS_BOLD, 0x002800u,
                            u002800_u0028FF_width,
                            u002800_u0028FF_height,
                            u002800_u0028FF_bits);
  builtinFonts.loadXbmFont(Font::TERMINUS_BOLD, 0x00E000u,
                            u00E000_u00E0FF_width,
                            u00E000_u00E0FF_height,
                            u00E000_u00E0FF_bits);
}

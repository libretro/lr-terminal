// Font loading
//
#include "fonts/default/u000000-u00007F-basic-latin.xbm"
#include "fonts/default/u000080-u0000FF-latin-1-supplement.xbm"
#include "fonts/default/u000100-u00017F-latin-extended-a.xbm"
//
#include "fonts/default/u002500-u00257F-box-drawing.xbm"
#include "fonts/default/u002580-u00259F-block-elements.xbm"
// TODO
// #include "fonts/default/u000180-u00024F-latin-extended-b.xbm"
// #include "fonts/default/u000250-u0002AF-IPA-extensions.xbm"
// #include "fonts/default/u000370-u0003FF-greek-coptic.xbm"
// #include "fonts/default/u000400-u0004FF-cyrillic.xbm"
// #include "fonts/default/u000500-u00052F-cyrillic-supplement.xbm"
// #include "fonts/default/u002000-u00206F-general-punctuation.xbm"
// #include "fonts/default/u002070-u00209F-superscript-subscript.xbm"
// #include "fonts/default/u0020A0-u0020CF-currency-symbols.xbm"
// #include "fonts/default/u002190-u0021FF-arrows.xbm"
// #include "fonts/default/u002200-u0022FF-mathematical-operators.xbm"
// #include "fonts/default/u002300-u0023FF-miscellaneous-technical.xbm"
// #include "fonts/default/u0025A0-u0025FF-geometric-shapes.xbm"
// #include "fonts/default/u002600-u0026FF-miscellaneous-symbols.xbm"
//
static void load(BuiltinFonts& builtinFonts)
{
  builtinFonts.loadXbmFont(Font::DEFAULT, 0x000000u,
                            u000000_u00007F_basic_latin_width,
                            u000000_u00007F_basic_latin_height,
                            u000000_u00007F_basic_latin_bits);
  builtinFonts.loadXbmFont(Font::DEFAULT, 0x000080u,
                            u000080_u0000FF_latin_1_supplement_width,
                            u000080_u0000FF_latin_1_supplement_height,
                            u000080_u0000FF_latin_1_supplement_bits);
  builtinFonts.loadXbmFont(Font::DEFAULT, 0x000100u,
                            u000100_u00017F_latin_extended_a_width,
                            u000100_u00017F_latin_extended_a_height,
                            u000100_u00017F_latin_extended_a_bits);
/*
  builtinFonts.loadXbmFont(Font::DEFAULT, 0x000180u,
                            u000180_u00024F_latin_extended_b_width,
                            u000180_u00024F_latin_extended_b_height,
                            u000180_u00024F_latin_extended_b_bits);
  builtinFonts.loadXbmFont(Font::DEFAULT, 0x000250u,
                            u000250_u0002AF_IPA_extensions_width,
                            u000250_u0002AF_IPA_extensions_height,
                            u000250_u0002AF_IPA_extensions_bits);
  builtinFonts.loadXbmFont(Font::DEFAULT, 0x000370u,
                            u000370_u0003FF_greek_coptic_width,
                            u000370_u0003FF_greek_coptic_height,
                            u000370_u0003FF_greek_coptic_bits);
  builtinFonts.loadXbmFont(Font::DEFAULT, 0x000400u,
                            u000400_u0004FF_cyrillic_width,
                            u000400_u0004FF_cyrillic_height,
                            u000400_u0004FF_cyrillic_bits);
  builtinFonts.loadXbmFont(Font::DEFAULT, 0x000500u,
                            u000500_u00052F_cyrillic_supplement_width,
                            u000500_u00052F_cyrillic_supplement_height,
                            u000500_u00052F_cyrillic_supplement_bits);
  builtinFonts.loadXbmFont(Font::DEFAULT, 0x002000u,
                            u002000_u00206F_general_punctuation_width,
                            u002000_u00206F_general_punctuation_height,
                            u002000_u00206F_general_punctuation_bits);
  builtinFonts.loadXbmFont(Font::DEFAULT, 0x002070u,
                            u002070_u00209F_superscript_subscript_width,
                            u002070_u00209F_superscript_subscript_height,
                            u002070_u00209F_superscript_subscript_bits);
  builtinFonts.loadXbmFont(Font::DEFAULT, 0x0020A0u,
                            u0020A0_u0020CF_currency_symbols_width,
                            u0020A0_u0020CF_currency_symbols_height,
                            u0020A0_u0020CF_currency_symbols_bits);
  builtinFonts.loadXbmFont(Font::DEFAULT, 0x002190u,
                            u002190_u0021FF_arrows_width,
                            u002190_u0021FF_arrows_height,
                            u002190_u0021FF_arrows_bits);
  builtinFonts.loadXbmFont(Font::DEFAULT, 0x002200u,
                            u002200_u0022FF_mathematical_operators_width,
                            u002200_u0022FF_mathematical_operators_height,
                            u002200_u0022FF_mathematical_operators_bits);
  builtinFonts.loadXbmFont(Font::DEFAULT, 0x002300u,
                            u002300_u0023FF_miscellaneous_technical_width,
                            u002300_u0023FF_miscellaneous_technical_height,
                            u002300_u0023FF_miscellaneous_technical_bits);
*/
  builtinFonts.loadXbmFont(Font::DEFAULT, 0x002500u,
                            u002500_u00257F_box_drawing_width,
                            u002500_u00257F_box_drawing_height,
                            u002500_u00257F_box_drawing_bits);
  builtinFonts.loadXbmFont(Font::DEFAULT, 0x002580u,
                            u002580_u00259F_block_elements_width,
                            u002580_u00259F_block_elements_height,
                            u002580_u00259F_block_elements_bits);
/*
  builtinFonts.loadXbmFont(Font::DEFAULT, 0x0025A0u,
                            u0025A0_u0025FF_geometric_shapes_width,
                            u0025A0_u0025FF_geometric_shapes_height,
                            u0025A0_u0025FF_geometric_shapes_bits);
  builtinFonts.loadXbmFont(Font::DEFAULT, 0x002600u,
                            u002600_u0026FF_miscellaneous_symbols_width,
                            u002600_u0026FF_miscellaneous_symbols_height,
                            u002600_u0026FF_miscellaneous_symbols_bits);
*/
}

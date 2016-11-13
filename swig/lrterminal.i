/* SWIG definition for the LR-Terminal interfaces available for non-C++ cores */
%module lrterminal
%{
#include "terminal_color.h"
#include "terminal_textstyle.h"
#include "terminal_console.h"
#include "terminal_terminal.h"
#include "terminal_log.h"
%}

%include "terminal_color.h"
%include "terminal_textstyle.h"
%include "terminal_console.h"
%include "terminal_terminal.h"
%include "terminal_log.h"

/* Since SWIG does not generate header files for the wrapper, */
/* it is easier to define a terminal() function to get the LRTerminal::Terminal instance, */
/* than it is to pass the instance to the wrapped language in the lrterminal.init() function. */
%{
#include "terminal_retro.h"
LRTerminal::Terminal* terminal()
{
    return &(LRTerminal::LibRetro::getInstance());
}
%}
LRTerminal::Terminal* terminal();

/* A way to easily convert a char* to a single char32_t */
%{
#include <locale>
#include <codecvt>
std::u32string _stringToU32String(const std::string str)
{
  // Convert from utf-8 char* to utf-32 char32_t* in order to update the console cells
  std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> u32conv;
  return u32conv.from_bytes(str);
}
char32_t codePoint(const char* in)
{
    char32_t ret = U'\0';
    std::string strIn = in;
    if (strIn != "")
    {
      std::u32string strU32 = _stringToU32String(std::string(in));
      ret = strU32[0];
    }
    return ret;
}
%}
char32_t codePoint(const char* in);

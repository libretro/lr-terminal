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

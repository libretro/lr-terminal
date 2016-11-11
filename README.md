# lr-terminal
A fake console library for [libretro](http://libretro.com).

Written in C++ and inspired by [libtcod](https://bitbucket.org/libtcod/libtcod),
this library provide a way to use a terminal-like display for libretro cores.
This library comes with a sample core written in C++ and a Lua core running games in a
way similar to [LÖVE](https://love2d.org/) or [Lutro](https://github.com/libretro/libretro-lutro),
and exposing the interfaces of the library to Lua through SWIG. An exemple of Lua game is provided
in the ressources and built along the Lua core.

# License
This software is released under the MIT License. See LICENSE for more info.

# Building
This library depends on [libretro-common](https://github.com/libretro/libretro-common).
The Lua core depends on [Lua 5.3](http://www.lua.org/) and [zlib](http://zlib.net/).
Those dependencies are automatically fetched with [cURL](https://curl.haxx.se/) when building.
[SWIG](http://swig.org/) is needed for generating the wrappers for the Lua core.

# Features and limitations
The console can use 24 bit colors and several fonts are built into the library.
Each cell of the console can be assigned a different foreground color, background colors,
code point and font. Other stylistic features are provided when printing blocks of characters,
like text alignment and box-drawing style.

The code points are coded into 32 bits, and the library expects string coded in utf-8
(they are internally converted to utf-32).
However, the library does not currently support unicode features like combining characters,
bidirectionnal text or full-width characters.
Each code point of a string is considered a different character.

The fonts are currently provided as xbm images in the ressources, and compiled into the library.
By changing the sources, other fonts can be provided, but it is also possible to define glyphs
in code with the "CUSTOM" font. This font does not initially contain any character.
Currently, the glyphs are 8x16 in pixel size and there is no way to change this.
All the provided font are in that size, even the 8x13 fonts from Xorg.
Because of the xbm format, the current built-in glyphs are monochrome, however,
the library supports greyscale glyphs (currently, only user-defined glyphs can use this feature).

The library provide access to states of libretro controllers.
The current model of the library represents up to four controllers
and the D-Pad, Start, Select, A, B, X, Y, L and R buttons.
Others buttons and analog sticks are not supported currently.
Other kinds of inputs, like mouse or keyboards, are not supported either.

The SWIG interface can be used to build wrappers for other languages, and build cores similar
to the provided Lua core.

The Lua core can load games contained in a directory or in a zip archives (with ztlua extension).
The Lua expects to find a `main.lua` file at the root of the given directory or archive,
in a similar way to LÖVE. Loading other lua files contained in the directory or archive is supported
through the Lua `require()` function. However, there is currently no way to load other kind of files
that could be contained in the archive or directory.

# Writing a core
When making a core using the lr-terminal library, the core must provide an implementation of
the `LRTerminal::Game` interface. This interface can be used for a stand-alone game
(like the sample core), or for a game-loading core (like the Lua core).
The `LRTerminal::Terminal` interface, implemented by the `LRTerminal::LibRetro` class, gives access
to the libretro functionnalities and the root console (the console rendered on screen).
It is possible to define off-screen consoles with the `LRTerminal::Console` class.
The `LRTerminal::TextStyle` class contains the various styling properties that can be used when
printing text or setting an individual console cell.
The `LRTerminal::Color` class represent a color. Many named colors are already defined,
like `LRTerminal::Color::red`, `LRTerminal::Color::darkGrey` or `LRTerminal::Color::lightestCyan`,
like in libtcod. Colors can also be defined from RGB, HSV or HSL values.
The `LRTerminal::log` function gives access to the logging capabilities of libretro.

The other classes and functions are used internally by the library. The fonts are loaded
inside the `LRTerminal::BuiltinFonts` class, and their loading functions are located in the `font.inc`
files located next to the xbm files in the ressources directory.

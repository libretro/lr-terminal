CPP = g++
CPPFLAGS = -g -O2 -Wall
SHARED = -fPIC -shared
LDFLAGS =
SWIG = swig
# Common Sources
COMMON_SRC = $(wildcard sources/*.cpp)
COMMON_OBJ = $(COMMON_SRC:.cpp=.o)
COMMON_INCLUDES = -I./includes -I./ressources -I./deps/libretro-common/include
# Sample core
SAMPLE_SRC = $(wildcard cores/sample/sources/*.cpp)
SAMPLE_OBJ = $(SAMPLE_SRC:.cpp=.o)
SAMPLE_INCLUDES = -I./cores/sample/includes
TARGET_SAMPLE = libretro_terminal_sample.so
# Lua core
LUA = lua-5.3.3
ZLIB = zlib-1.2.8
LUA_OBJ = deps/$(LUA)/src/liblua.a
ZLIB_OBJ = deps/$(ZLIB)/contrib/minizip/unzip.o deps/$(ZLIB)/contrib/minizip/ioapi.o deps/$(ZLIB)/libz.a
LUA_CORE_SRC = $(wildcard cores/lua/sources/*.cpp)
LUA_CORE_OBJ = $(LUA_CORE_SRC:.cpp=.o)
LUA_CORE_INCLUDES = -I./cores/lua/includes -I./deps/$(LUA)/src -I./deps/$(ZLIB) -I./deps/$(ZLIB)/contrib/minizip
LUA_CORE_SWIG_DIR = ./swig/lua
LUA_CORE_SWIG_SRC = $(LUA_CORE_SWIG_DIR)/lrterminal_lua.cpp
LUA_CORE_SWIG_OBJ = $(LUA_CORE_SWIG_SRC:.cpp=.o)
LUA_CORE_SWIG_INCLUDES = -I$(LUA_CORE_SWIG_DIR)
TARGET_LUA_CORE = libretro_terminal_lua.so
# Sample for Lua core
LUA_CORE_SAMPLE_SRC = $(wildcard ressources/lua_sample/*)
TARGET_LUA_CORE_SAMPLE = lua_sample.ztlua

all: sample_core lua_core
sample_core: $(TARGET_SAMPLE)
lua_core: $(TARGET_LUA_CORE) $(TARGET_LUA_CORE_SAMPLE)

# Dependencies for common
deps:
	mkdir -p deps

deps/libretro-common/include/libretro.h: deps
	if [ ! -e $@ ]; then cd deps && git clone https://github.com/libretro/libretro-common; fi

# Common
sources/%.o: sources/%.cpp deps/libretro-common/include/libretro.h
	$(CPP) $(SHARED) $(CPPFLAGS) $(COMMON_INCLUDES) -o $@ -c $<

# Sample core
cores/sample/sources/%.o: cores/sample/sources/%.cpp
	$(CPP) $(SHARED) $(CPPFLAGS) $(COMMON_INCLUDES) $(SAMPLE_INCLUDES) -o $@ -c $<

$(TARGET_SAMPLE): $(COMMON_OBJ) $(SAMPLE_OBJ)
	$(CPP) $(SHARED) $(LDFLAGS) -o $@ $(SAMPLE_OBJ) $(COMMON_OBJ)

# Dependencies for Lua core
deps/$(LUA)/src/lua.hpp: deps
	if [ ! -e $@ ]; then cd deps && curl -O http://www.lua.org/ftp/$(LUA).tar.gz && tar -xf $(LUA).tar.gz; fi

deps/$(ZLIB)/contrib/minizip/unzip.h: deps
	if [ ! -e $@ ]; then cd deps && curl -O http://zlib.net/$(ZLIB).tar.gz && tar -xf $(ZLIB).tar.gz; fi

# TODO: the target depends on the OS
deps/$(LUA)/src/liblua.a:
	cd deps/$(LUA)/src \
	&& make posix MYCFLAGS="$(SHARED)"

deps/$(ZLIB)/libz.a:
	cd deps/$(ZLIB) \
	&& ./configure --static \
	&& make CFLAGS="-O3 -D_LARGEFILE64_SOURCE=1 -DHAVE_HIDDEN $(SHARED)"

deps/$(ZLIB)/contrib/minizip/%.o: deps/$(ZLIB)/libz.a
	cd deps/$(ZLIB)/contrib/minizip \
	&& make CFLAGS="-O -I../.. $(SHARED)"

# Lua core
cores/lua/sources/%.o: cores/lua/sources/%.cpp deps/$(LUA)/src/lua.hpp deps/$(ZLIB)/contrib/minizip/unzip.h
	$(CPP) $(SHARED) $(CPPFLAGS) $(COMMON_INCLUDES) $(LUA_CORE_INCLUDES) -o $@ -c $<

$(LUA_CORE_SWIG_OBJ): $(LUA_CORE_SWIG_SRC)
	$(CPP) $(SHARED) $(CPPFLAGS) $(COMMON_INCLUDES) -o $@ -c $<

$(LUA_CORE_SWIG_SRC): swig/lrterminal.i
	mkdir -p $(LUA_CORE_SWIG_DIR)
	$(SWIG) -c++ $(COMMON_INCLUDES) -lua -o $(LUA_CORE_SWIG_SRC) swig/lrterminal.i

$(TARGET_LUA_CORE): $(COMMON_OBJ) $(LUA_CORE_OBJ) $(LUA_CORE_SWIG_OBJ) $(LUA_OBJ) $(ZLIB_OBJ)
	$(CPP) $(SHARED) $(LDFLAGS) -o $@ $(LUA_CORE_SWIG_OBJ) $(LUA_CORE_OBJ) $(LUA_OBJ) $(ZLIB_OBJ) $(COMMON_OBJ)

$(TARGET_LUA_CORE_SAMPLE): $(LUA_CORE_SAMPLE_SRC)
	cd ressources/lua_sample && zip -r ../../$@ *

.PHONY: clean

clean:
	rm -f $(COMMON_OBJ)
	rm -f $(SAMPLE_OBJ)
	rm -f $(LUA_CORE_OBJ)
	rm -f $(LUA_CORE_SWIG_OBJ)
	rm -f $(TARGET_SAMPLE)
	rm -f $(TARGET_LUA_CORE)
	rm -rf $(LUA_CORE_SWIG_DIR)
	rm -f $(TARGET_LUA_CORE_SAMPLE)
	cd deps/$(ZLIB) && make clean
	cd deps/$(ZLIB)/contrib/minizip && make clean
	cd deps/$(LUA) && make clean

deps_clean:
	rm -rf deps

run:
	retroarch -v -L $(TARGET_SAMPLE) .
gdb:
	gdb --ex run --args retroarch -v -L $(TARGET_SAMPLE) .

run_lua:
	retroarch -v -L $(TARGET_LUA_CORE) $(TARGET_LUA_CORE_SAMPLE)

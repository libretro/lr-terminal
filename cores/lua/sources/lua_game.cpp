#include "lua_game.h"
#include "terminal_log.h"
#include <fstream>
#include <sstream>
#include <cstring>
// For checking the file type
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>



// SWIG definitions
extern "C"
{
  extern int luaopen_lrterminal(lua_State* L);
}

LRTerminal::GameInterface& getGameInstance(void)
{
  return LRTLua::Game::getInstance();
}

void destroyGameInstance(void)
{
  LRTLua::Game::destroyInstance();
}

namespace LRTLua
{
  // Game

  Game* Game::m_instance = NULL;

  // The Game instance is a singleton
  Game& Game::getInstance(void)
  {
    if (m_instance == NULL)
    {
      m_instance = new Game();
    }
    return *m_instance;
  }
  void Game::destroyInstance(void)
  {
    delete m_instance;
    m_instance = NULL;
  }

  ////
  // Constructor
  Game::Game(void):
      m_terminal(NULL),
      m_filePath(""),
      m_isDirectory(false),
      m_zipfile(NULL),
      m_Lua(NULL),
      m_terminalWidth(80u),
      m_terminalHeight(25u)
  {
  }

  // Load a game
  bool Game::load(const std::string& path)
  {
    bool ret = false;
    // Check if path is directory or zip file, and check the presence of main.lua
    ret = _checkAndOpenFile(path);
    if (ret)
    {
      // Create the lua state
      _openLuaState();
      // Load the main.lua file into the state
      ret = _loadMainLua();
      if (ret)
      {
        // Lua call: lrterminal.conf
        _callLrTerminalConf();
      }
    }
    return ret;
  }

  // Unload a game
  void Game::unload(void)
  {
    // Call lua: lrterminal.deinit
    _callLrTerminalDeinit();
    // Close the lua state
    _closeLuaState();
    // Close the archive
    _closeFile();
  }

  // Reset a game
  void Game::reset(void)
  {
    // Call lua: lrterminal.deinit
    _callLrTerminalDeinit();
    // Close the lua state
    _closeLuaState();
    // Create the state and load the files again
    _openLuaState();
    _loadMainLua();
    // Call lua: lrterminal.init
    _callLrTerminalInit();
  }

  // Get the Terminal
  void Game::initialize(LRTerminal::Terminal& terminal)
  {
    m_terminal = &terminal;
    // Call lua: lrterminal.init
    _callLrTerminalInit();
  }

  // Update a game for a frame
  void Game::update(double deltaTime)
  {
    // Call lua: lrterminal.update
    lua_getglobal(m_Lua, "lrterminal");
    lua_getfield(m_Lua, -1, "update");
    if (lua_isfunction(m_Lua, -1))
    {
      lua_pushnumber(m_Lua, deltaTime);
      if (lua_pcall(m_Lua, 1, 0, 0))
      {
        log(LRTerminal::LogLevel::ERROR, "%s\n", lua_tostring(m_Lua, -1));
        lua_pop(m_Lua, 1);
      }
    }
    lua_pop(m_Lua, 1);
  }

  // Get the terminal width in characters
  unsigned Game::getTerminalWidth() const
  {
    return m_terminalWidth;
  }

  // Get the terminal height in characters
  unsigned Game::getTerminalHeight() const
  {
    return m_terminalHeight;
  }

  // Get the core name
  static const std::string C_LIBRARY_NAME("lr-terminal-lua");
  const std::string& Game::getCoreName(void) const
  {
    return C_LIBRARY_NAME;
  }

  // Get the core version
  static const std::string C_LIBRARY_VERSION("v0.1");
  const std::string& Game::getCoreVersion(void) const
  {
    return C_LIBRARY_VERSION;
  }

  // Get the list of supported extensions for the core
  void Game::getExtensionList(std::list<std::string>& extList) const
  {
    extList.push_back("ztlua");
  }

  // Supports running without game ?
  bool Game::supportNoGame(void) const
  {
    return false;
  }

  // Check if the file is a directory or an archive, open it and check the presence of main.lua
  bool Game::_checkAndOpenFile(const std::string& path)
  {
    bool ret = false;
    m_filePath = path;
    struct stat st;
    int pathExist = stat(path.c_str(), &st);
    if (pathExist == 0)
    {
      if (S_ISDIR(st.st_mode))
      {
        // The path is a directory
        m_isDirectory = true;
        // Check if there is main.lua in the directory
        std::string mainLuaPath = path + "/main.lua";
        pathExist = stat(mainLuaPath.c_str(), &st);
        if ((pathExist == 0) && S_ISREG(st.st_mode))
        {
          // The main.lua file exists and the file is regular => OK
          ret = true;
        }
        else
        {
          log(LRTerminal::LogLevel::ERROR, "main.lua does not exists in directory %s\n", path.c_str());
        }
      }
      else
      {
        // The path is assumed to be a zip archive
        m_isDirectory = false;
        // Open the archive and check the presence of main.lua at the root of the archive
        m_zipfile = unzOpen(path.c_str());
        if (m_zipfile != NULL)
        {
          // Check the presence of main.lua in the archive
          if (UNZ_OK == unzLocateFile(m_zipfile, "main.lua", 0))
          {
            ret = true;
          }
          else
          {
            log(LRTerminal::LogLevel::ERROR, "main.lua does not exists in archive %s\n", path.c_str());
          }
        }
        else
        {
          log(LRTerminal::LogLevel::ERROR, "%s is not a supported archive.\n", path.c_str());
        }
      }
    }
    else
    {
      log(LRTerminal::LogLevel::ERROR, "%s: no such file or directory.\n", path.c_str());
    }
    return ret;
  }

  // Close the file
  void Game::_closeFile(void)
  {
    if (!m_isDirectory)
    {
      unzClose(m_zipfile);
    }
    m_zipfile = NULL;
    m_isDirectory = false;
  }

  // Open the lua state
  void Game::_openLuaState(void)
  {
    m_Lua = luaL_newstate();
    luaL_openlibs(m_Lua);
    // Add the lrterminal API
    luaopen_lrterminal(m_Lua);
    // Add the custom loader
    lua_register(m_Lua, "LrTerminalLoader", &luaLoader);
    luaL_dostring(m_Lua, "table.insert(package.searchers, 2, LrTerminalLoader)\n");
    // Add the default lrterminal functions (conf, init, update, deinit)
    // lrterminal object should already exists thanks to the call to luaopen_lrterminal
    luaL_dostring(m_Lua, "lrterminal.conf = function(settings) end\n");
    luaL_dostring(m_Lua, "lrterminal.init = function() end\n");
    luaL_dostring(m_Lua, "lrterminal.update = function(deltaTime) end\n");
    luaL_dostring(m_Lua, "lrterminal.deinit = function() end\n");
    // Settings table
    lua_getglobal(m_Lua, "lrterminal");
    lua_newtable(m_Lua);
    lua_pushnumber(m_Lua, m_terminalWidth);
    lua_setfield(m_Lua, -2, "width");
    lua_pushnumber(m_Lua, m_terminalHeight);
    lua_setfield(m_Lua, -2, "height");
    lua_setfield(m_Lua, -2, "settings");
    lua_pop(m_Lua, 1);
   }

  // Close the lua state
  void Game::_closeLuaState(void)
  {
    lua_close(m_Lua);
    m_Lua = NULL;
  }

  // Load main.lua
  bool Game::_loadMainLua(void)
  {
    bool ret = false;
    std::string contents;
    if (_getFileContents("main.lua", contents))
    {
      luaL_dostring(m_Lua, contents.c_str());
      ret = true;
    }
    return ret;
  }

  // Call Lua: lrterminal.conf
  void Game::_callLrTerminalConf(void)
  {
    lua_getglobal(m_Lua, "lrterminal");
    lua_getfield(m_Lua, -1, "conf");
    if (lua_isfunction(m_Lua, -1))
    {
      lua_getfield(m_Lua, -2, "settings");
      if (lua_pcall(m_Lua, 1, 0, 0))
      {
        log(LRTerminal::LogLevel::ERROR, "%s\n", lua_tostring(m_Lua, -1));
        lua_pop(m_Lua, 1);
      }
    }
    // read the values width and height of settings
    lua_getfield(m_Lua, -1, "settings");
    lua_getfield(m_Lua, -1, "width");
    m_terminalWidth = luaL_checkinteger(m_Lua, -1);
    lua_pop(m_Lua, 1);
    lua_getfield(m_Lua, -1, "height");
    m_terminalHeight = luaL_checkinteger(m_Lua, -1);
    lua_pop(m_Lua, 3);
  }

  // Call Lua: lrterminal.init
  void Game::_callLrTerminalInit(void)
  {
    lua_getglobal(m_Lua, "lrterminal");
    lua_getfield(m_Lua, -1, "init");
    if (lua_isfunction(m_Lua, -1))
    {
      if (lua_pcall(m_Lua, 0, 0, 0))
      {
        log(LRTerminal::LogLevel::ERROR, "%s\n", lua_tostring(m_Lua, -1));
        lua_pop(m_Lua, 1);
      }
    }
    lua_pop(m_Lua, 1);
  }

  // Call Lua: lrterminal.deinit
  void Game::_callLrTerminalDeinit(void)
  {
    lua_getglobal(m_Lua, "lrterminal");
    lua_getfield(m_Lua, -1, "deinit");
    if (lua_isfunction(m_Lua, -1))
    {
      if (lua_pcall(m_Lua, 0, 0, 0))
      {
        log(LRTerminal::LogLevel::ERROR, "%s\n", lua_tostring(m_Lua, -1));
        lua_pop(m_Lua, 1);
      }
    }
    lua_pop(m_Lua, 1);
  }

  // Special loader for lua when using a require for files inside the archive
  // Lua callback
  int Game::luaLoader(lua_State* L)
  {
    return getInstance()._luaLoader(L);
  }
  // Loader function
  int Game::_luaLoader(lua_State* L)
  {
    int ret = 0;
    const char* moduleName = luaL_checkstring(L, 1);
    if (moduleName)
    {
      std::string fileName = std::string(moduleName) + ".lua";
      std::string fileContents;
      if (_getFileContents(fileName, fileContents))
      {
        luaL_loadbuffer(L, fileContents.c_str(), fileContents.size(), fileName.c_str());
        ret = 1;
      }
    }
    return ret;
  }

  // Get the contents of a file
  // Returns false if the file cannot be read
  bool Game::_getFileContents(const std::string& relativePath, std::string& contents)
  {
    bool ret = false;
    if (m_isDirectory)
    {
      std::ifstream file(m_filePath + "/" + relativePath);
      if (file)
      {
        std::stringstream str;
        str << file.rdbuf();
        contents = str.str();
        ret = true;
      }
      file.close();
    }
    else
    {
      // Locate the file in the archive
      if (UNZ_OK == unzLocateFile(m_zipfile, relativePath.c_str(), 0))
      {
        // Get the file infos
        unz_file_info fileInfo;
        unzGetCurrentFileInfo(m_zipfile, &fileInfo, NULL, 0u, NULL, 0u, NULL, 0u);
        // open the file
        if (UNZ_OK == unzOpenCurrentFile(m_zipfile))
        {
          char* buffer = new char[fileInfo.uncompressed_size + 1u];
          memset(buffer, 0u, fileInfo.uncompressed_size + 1u);
          if (0 < unzReadCurrentFile(m_zipfile, buffer, fileInfo.uncompressed_size + 1u))
          {
            // File is read
            contents = buffer;
            ret = true;
          }
          delete[] buffer;
          unzCloseCurrentFile(m_zipfile);
        }
      }
    }
    return ret;
  }

}

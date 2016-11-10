
#ifndef _LUA_GAME__H_
#define _LUA_GAME__H_

#include "terminal_game.h"
#include "terminal_terminal.h"
#include "minizip/unzip.h"
#include "lua.hpp"


// Sample game for what could be done in a core based on LR-Terminal
namespace LRTLua
{
  class Game: public LRTerminal::GameInterface
  {
  public:
    // The Game instance is a singleton
    static Game& getInstance(void);
    static void destroyInstance(void);

    // Load a game
    virtual bool load(const std::string& path);

    // Unload a game
    virtual void unload(void);

    // Reset a game
    virtual void reset(void);

    // Initialize a game. This method is called after successfully loading, and before the first update.
    // The Terminal is only accessible to the game instance when this method is called
    virtual void initialize(LRTerminal::Terminal& terminal);

    // Update a game for a frame
    virtual void update(double deltaTime);

    // Get the terminal width in characters
    virtual unsigned getTerminalWidth() const;

    // Get the terminal height in characters
    virtual unsigned getTerminalHeight() const;

    // Get the core name
    virtual const std::string& getCoreName(void) const;

    // Get the core version
    virtual const std::string& getCoreVersion(void) const;

    // Get the list of supported extensions for the core
    virtual void getExtensionList(std::list<std::string>& extList) const;

    // Supports running without game ?
    virtual bool supportNoGame(void) const;

  private:
    // Constructor is private, the game is accessed externally with the getInstance() and destroyInstance()
    Game();

    // Check if the file is a directory or an archive, open it and check the presence of main.lua
    bool _checkAndOpenFile(const std::string& path);
    // Close the file
    void _closeFile(void);

    // Open the lua state
    void _openLuaState(void);
    // Close the lua state
    void _closeLuaState(void);

    // Load main.lua
    bool _loadMainLua(void);

    // Call Lua: lrterminal.conf
    void _callLrTerminalConf(void);
    // Call Lua: lrterminal.init
    void _callLrTerminalInit(void);
    // Call Lua: lrterminal.deinit
    void _callLrTerminalDeinit(void);

    // Special loader for lua when using a require for files inside the archive
    // Lua callback
    static int luaLoader(lua_State* L);
    // Loader function
    int _luaLoader(lua_State* L);

    // Get the contents of a file
    // Returns false if the file cannot be read
    bool _getFileContents(const std::string& relativePath, std::string& contents);

    // Instance
    static Game* m_instance;

    // Terminal to call for various infos (render frame, input state, ...)
    LRTerminal::Terminal* m_terminal;

    // File path of the game
    std::string m_filePath;

    // Is the game path a directory or an archive ?
    bool m_isDirectory;

    // Zip file of the game
    unzFile m_zipfile;

    // Lua stack
    lua_State* m_Lua;

    // Terminal dimensions
    unsigned m_terminalWidth;
    unsigned m_terminalHeight;
  };
}

#endif

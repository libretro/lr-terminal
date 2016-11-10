
#ifndef _TERMINAL_GAME__H_
#define _TERMINAL_GAME__H_

#include <string>
#include <list>


namespace LRTerminal
{
  // Defined in terminal_frontend.h
  class Terminal;

  // This class represents a game, and all the data associated to a game
  class GameInterface
  {
  public:
    // Destructor
    virtual ~GameInterface();

    // Load a game
    virtual bool load(const std::string& path) = 0;

    // Unload a game
    virtual void unload(void) = 0;

    // Reset a game. Should have the same effect as unloading it and loading it again.
    virtual void reset(void) = 0;

    // Initialize a game. This method is called after successfully loading, and before the first update.
    // The Terminal is only accessible to the game instance when this method is called
    virtual void initialize(LRTerminal::Terminal& frontend) = 0;

    // Update a game for a frame
    virtual void update(double deltaTime) = 0;

    // Get the terminal width in characters
    virtual unsigned getTerminalWidth(void) const = 0;

    // Get the terminal height in characters
    virtual unsigned getTerminalHeight(void) const = 0;

    // Get the core name
    virtual const std::string& getCoreName(void) const = 0;

    // Get the core version
    virtual const std::string& getCoreVersion(void) const = 0;

    // Get the list of supported extensions for the core
    virtual void getExtensionList(std::list<std::string>& extList) const = 0;

    // Supports running without game ?
    // Return true if the core does not need games, false otherwise.
    virtual bool supportNoGame(void) const = 0;
  };
}

// Implementations of GameInterface must implement this function to get the game instance
// This function is called by the LRTerminal::Retro class in its constructor
LRTerminal::GameInterface& getGameInstance(void);
// Destructor for the GameInterface, called in the LRTerminal::Retro destructor
void destroyGameInstance(void);


#endif

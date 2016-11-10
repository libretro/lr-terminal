
#ifndef _SAMPLE_GAME__H_
#define _SAMPLE_GAME__H_

#include "terminal_game.h"
#include <string>
#include <list>
#include "terminal_console.h"
#include "terminal_terminal.h"

#include "sample_controller.h"
#include "sample_colors.h"
#include "sample_styles.h"


// Sample game for what could be done in a core based on LR-Terminal
namespace Sample
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

    // Instance
    static Game* m_instance;

    // Terminal to call for various infos (render frame, input state, ...)
    LRTerminal::Terminal* m_terminal;

    // Terminal infos
    // Terminal size in characters
    unsigned m_terminalWidth;
    unsigned m_terminalHeight;

    // For changing pages
    bool m_wasDownL;
    bool m_wasDownR;
    bool m_wasDownStart;

    // Controller page
    ShowControlerPage m_controllerPage;
    ColorPage m_colorPage;
    StylesPage m_stylesPage;

    // List of pages
    std::list<Page*> m_pages;
    std::list<Page*>::iterator m_currentPage;
  };
}

#endif

#include "sample_game.h"
#include "terminal_terminal.h"
#include "terminal_color.h"
#include "terminal_console.h"
#include "terminal_log.h"

using namespace LRTerminal;

LRTerminal::GameInterface& getGameInstance(void)
{
  return Sample::Game::getInstance();
}

void destroyGameInstance(void)
{
  Sample::Game::destroyInstance();
}

namespace Sample
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
      m_terminalWidth(80u),
      m_terminalHeight(25u),
      m_wasDownL(false),
      m_wasDownR(false),
      m_wasDownStart(false),
      m_controllerPage(m_terminalWidth, m_terminalHeight),
      m_colorPage(m_terminalWidth, m_terminalHeight),
      m_stylesPage(m_terminalWidth, m_terminalHeight)
  {
    m_pages.push_back(&m_controllerPage);
    m_pages.push_back(&m_colorPage);
    m_pages.push_back(&m_stylesPage);
    m_currentPage = m_pages.begin();
  }

  // Load a game
  bool Game::load(const std::string& path)
  {
    // Nothing to do, the sample game does not need to load data
    return true;
  }

  // Unload a game
  void Game::unload(void)
  {
    // Nothing to do
  }

  // Reset a game
  void Game::reset(void)
  {
    unload();
    load("");
  }

  // Get the Terminal
  void Game::initialize(LRTerminal::Terminal& terminal)
  {
    m_terminal = &terminal;
    m_controllerPage.initialize(terminal);
    m_colorPage.initialize(terminal);
    m_stylesPage.initialize(terminal);
  }

  // Update a game for a frame
  void Game::update(double deltaTime)
  {
    LRTerminal::log(LogLevel::INFO, "Delta Time: %f\n", deltaTime);
    // Check if we must change page
    bool isDownL = m_terminal->isKeyDown(PlayerInput::PLAYER_1, JoypadKeyInput::L);
    bool isDownR = m_terminal->isKeyDown(PlayerInput::PLAYER_1, JoypadKeyInput::R);
    bool isDownStart = m_terminal->isKeyDown(PlayerInput::PLAYER_1, JoypadKeyInput::START);
    // We dont repeat the commands if a command was done previously
    if (!m_wasDownR || !m_wasDownStart)
    {
      // Check if we go next
      if (isDownR && isDownStart)
      {
        // Goto next page
        ++m_currentPage;
        if (m_currentPage == m_pages.end())
        {
          m_currentPage = m_pages.begin();
        }
      }
    }
    if (!m_wasDownL || !m_wasDownStart)
    {
      // Check if we go previous
      if (isDownL && isDownStart)
      {
        // Goto previous page
        if (m_currentPage == m_pages.begin())
        {
          m_currentPage = m_pages.end();
        }
        --m_currentPage;
      }
    }
    m_wasDownL = isDownL;
    m_wasDownR = isDownR;
    m_wasDownStart = isDownStart;

    // Update the current page
    (*m_currentPage)->update(deltaTime);
    //
    Console& rootConsole = m_terminal->getRootConsole();
    TextStyle style = rootConsole.getDefaultStyle();
    style.setAlignment(Alignment::CENTER);
    rootConsole.print(m_terminalWidth / 2, m_terminalHeight - 1, style,
                      "START+L: previous page -- START+R: next page");
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

  // Core name
  static const std::string C_LIBRARY_NAME("lr-terminal-sample");
  const std::string& Game::getCoreName(void) const
  {
    return C_LIBRARY_NAME;
  }

  // Core version
  static const std::string C_LIBRARY_VERSION("v0.1");
  const std::string& Game::getCoreVersion(void) const
  {
    return C_LIBRARY_VERSION;
  }

  // Get the list of supported extensions for the core
  void Game::getExtensionList(std::list<std::string>& extList) const
  {
  }

  // Supports running without game ?
  bool Game::supportNoGame(void) const
  {
    return true;
  }

}

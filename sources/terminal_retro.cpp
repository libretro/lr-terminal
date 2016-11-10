#include "terminal_retro.h"
#include "terminal_game.h"
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdarg>

namespace LRTerminal
{

  ////
  // Constants
  // FPS
  static const double C_FPS = 60.0;

  // Default logging callback
  // Output to stderr
  void defaultLogCallback(enum retro_log_level level, const char *fmt, ...)
  {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
  }

  // Input descriptors

  static const struct retro_input_descriptor C_INPUT_DESCRIPTORS[] = {
    // Player 1
    { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_B, "Player 1 - Joypad B" },
    { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_Y, "Player 1 - Joypad Y" },
    { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_SELECT, "Player 1 - Joypad Select" },
    { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_START, "Player 1 - Joypad Start" },
    { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT, "Player 1 - Joypad Left" },
    { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP, "Player 1 - Joypad Up" },
    { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN, "Player 1 - Joypad Down" },
    { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT, "Player 1 - Joypad Right" },
    { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_A, "Player 1 - Joypad A" },
    { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_X, "Player 1 - Joypad X" },
    { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L, "Player 1 - Joypad L" },
    { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R, "Player 1 - Joypad R" },
    // Player 2
    { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_B, "Player 2 - Joypad B" },
    { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_Y, "Player 2 - Joypad Y" },
    { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_SELECT, "Player 2 - Joypad Select" },
    { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_START, "Player 2 - Joypad Start" },
    { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT, "Player 2 - Joypad Left" },
    { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP, "Player 2 - Joypad Up" },
    { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN, "Player 2 - Joypad Down" },
    { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT, "Player 2 - Joypad Right" },
    { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_A, "Player 2 - Joypad A" },
    { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_X, "Player 2 - Joypad X" },
    { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L, "Player 2 - Joypad L" },
    { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R, "Player 2 - Joypad R" },
    // Player 3
    { 2, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_B, "Player 3 - Joypad B" },
    { 2, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_Y, "Player 3 - Joypad Y" },
    { 2, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_SELECT, "Player 3 - Joypad Select" },
    { 2, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_START, "Player 3 - Joypad Start" },
    { 2, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT, "Player 3 - Joypad Left" },
    { 2, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP, "Player 3 - Joypad Up" },
    { 2, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN, "Player 3 - Joypad Down" },
    { 2, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT, "Player 3 - Joypad Right" },
    { 2, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_A, "Player 3 - Joypad A" },
    { 2, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_X, "Player 3 - Joypad X" },
    { 2, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L, "Player 3 - Joypad L" },
    { 2, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R, "Player 3 - Joypad R" },
    // Player 4
    { 3, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_B, "Player 4 - Joypad B" },
    { 3, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_Y, "Player 4 - Joypad Y" },
    { 3, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_SELECT, "Player 4 - Joypad Select" },
    { 3, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_START, "Player 4 - Joypad Start" },
    { 3, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT, "Player 4 - Joypad Left" },
    { 3, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP, "Player 4 - Joypad Up" },
    { 3, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN, "Player 4 - Joypad Down" },
    { 3, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT, "Player 4 - Joypad Right" },
    { 3, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_A, "Player 4 - Joypad A" },
    { 3, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_X, "Player 4 - Joypad X" },
    { 3, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L, "Player 4 - Joypad L" },
    { 3, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R, "Player 4 - Joypad R" },
    // No more players
    { 0, 0, 0, 0, NULL },
  };

  ////
  // LibRetro class implementation

  // Singleton Instance
  LibRetro* LibRetro::m_instance = NULL;

  LibRetro& LibRetro::getInstance(void)
  {
    if (NULL == m_instance)
    {
      m_instance = new LibRetro();
    }
    return *m_instance;
  }

  void LibRetro::destroyInstance(void)
  {
    delete m_instance;
    m_instance = NULL;
  }

  // Constructor
  LibRetro::LibRetro(void):
      m_game(getGameInstance()),
      m_rootConsole(NULL),
      m_environmentCallback(NULL),
      m_videoRefreshCallback(NULL),
      m_audioSampleCallback(NULL),
      m_audioSampleBatchCallback(NULL),
      m_inputPollCallback(NULL),
      m_inputStateCallback(NULL),
      m_logCallback(defaultLogCallback),
      m_canDupe(false),
      m_deltaTime(1.0 / C_FPS),
      m_supportNoGame(m_game.supportNoGame()),
      m_libraryName(m_game.getCoreName()),
      m_libraryVersion(m_game.getCoreVersion()),
      m_validExtensions("")

  {
    // Get the extension list from the core
    std::list<std::string> extLst;
    m_game.getExtensionList(extLst);
    m_validExtensions = "";
    if ((!extLst.empty()))
    {
      m_validExtensions.append(extLst.front());
      extLst.pop_front();
      for (auto iter = extLst.begin(); iter != extLst.end(); ++iter)
      {
        m_validExtensions.append("|").append(*iter);
      }
    }
  }

  // Destructor
  LibRetro::~LibRetro(void)
  {
    // Destroy the game instance
    destroyGameInstance();
  }


  ////
  // LibRetro core functions
  void LibRetro::init()
  {
  }

  void LibRetro::deinit()
  {
  }

  void LibRetro::getSystemInfo(struct retro_system_info *info) const
  {
    memset(info, 0u, sizeof(struct retro_system_info));
    info->library_name = m_libraryName.c_str();
    info->library_version = m_libraryVersion.c_str();
    info->valid_extensions = m_validExtensions.c_str();
    info->need_fullpath = true;
    info->block_extract = false;
  }

  void LibRetro::getSystemAudioVideoInfo(struct retro_system_av_info *info) const
  {
    // Retrieve the infos from the game data
    unsigned width = m_rootConsole->getFontWidth() * m_game.getTerminalWidth();
    unsigned height = m_rootConsole->getFontHeight() * m_game.getTerminalHeight();

    // Set the geometry infos
    info->geometry.base_width = width;
    info->geometry.base_height = height;
    info->geometry.max_width = width;
    info->geometry.max_height = height;
    info->geometry.aspect_ratio = 0.0;
    LRTerminal::log(LogLevel::INFO, "Width: %u, Height: %u\n", width, height);

    // Set the timing infos
    info->timing.fps = C_FPS; // 60 FPS, may be configurable later
    info->timing.sample_rate = 44100.0; // 44.1 kHz, may b configurable later
  }

  void LibRetro::setControllerPortDevice(unsigned port, unsigned device)
  {
    LRTerminal::log(LogLevel::INFO, "Port: %u, Device: %u", port, device);
  }

  ////
  // Game functions

  void LibRetro::resetGame(void)
  {
    m_game.reset();
  }

  bool LibRetro::loadGame(const std::string& path)
  {
    // Set the pixel format
    // If the pixel format used internally in lr-terminal is not supported, fail to load a game
    enum retro_pixel_format fmt = RETRO_PIXEL_FORMAT_XRGB8888;
    if (!_environment(RETRO_ENVIRONMENT_SET_PIXEL_FORMAT, &fmt))
    {
       m_logCallback(RETRO_LOG_INFO, "XRGB_8888 is not supported.\n");
       return false;
    }
    // Load the game
    bool ret = m_game.load(path);
    if (ret)
    {
      // Initialize the root console
      m_rootConsole = new RootConsole(m_game.getTerminalWidth(),  m_game.getTerminalHeight());
      // Initialize the game
      m_game.initialize(*this);
    }
    return ret;
  }

  void LibRetro::unloadGame(void)
  {
    m_game.unload();
    // Destroy the root console
    delete m_rootConsole;
    m_rootConsole = NULL;
  }

  void LibRetro::runGame(void)
  {
    _inputPoll();
    m_game.update(m_deltaTime);
    unsigned width = m_rootConsole->getFontWidth() * m_game.getTerminalWidth();
    unsigned height = m_rootConsole->getFontHeight() * m_game.getTerminalHeight();
    unsigned pitch = width * sizeof(uint32_t);
    bool isUpdated = false;
    const uint32_t* image = m_rootConsole->renderImage(isUpdated);
    if (m_canDupe && (!isUpdated))
    {
      _videoRefresh(NULL, width, height, pitch);
    }
    else
    {
      _videoRefresh(image, width, height, pitch);
    }
  }

  ////
  // Setter for callbacks
  void LibRetro::setEnvironment(retro_environment_t& cb)
  {
    m_environmentCallback = cb;
    // Set the input descriptors
    _environment(RETRO_ENVIRONMENT_SET_INPUT_DESCRIPTORS,
                 const_cast<retro_input_descriptor*>(C_INPUT_DESCRIPTORS));

    // Get the log callback if available
    // If not available, a default callback is used
    struct retro_log_callback logcb;
    if (_environment(RETRO_ENVIRONMENT_GET_LOG_INTERFACE, &logcb))
    {
      m_logCallback = logcb.log;
    }

    // Check if duplicated images can be dropped during rendering
    bool canDupe;
    if (_environment(RETRO_ENVIRONMENT_GET_CAN_DUPE, &canDupe))
    {
      m_canDupe = canDupe;
    }

    // Set the Frame Time callback
    struct retro_frame_time_callback timeCb;
    timeCb.callback = &LibRetro::_timeCallback;
    timeCb.reference = 1000000 / C_FPS;
    _environment(RETRO_ENVIRONMENT_SET_FRAME_TIME_CALLBACK, &timeCb);

    // Indicate if we need games
    _environment(RETRO_ENVIRONMENT_SET_SUPPORT_NO_GAME, &m_supportNoGame);
  }

  void LibRetro::setVideoRefresh(retro_video_refresh_t& cb)
  {
    m_videoRefreshCallback = cb;
  }

  void LibRetro::setAudioSample(retro_audio_sample_t& cb)
  {
    m_audioSampleCallback = cb;
  }

  void LibRetro::setAudioSampleBatch(retro_audio_sample_batch_t& cb)
  {
    m_audioSampleBatchCallback = cb;
  }

  void LibRetro::setInputPoll(retro_input_poll_t& cb)
  {
    m_inputPollCallback = cb;
  }

  void LibRetro::setInputState(retro_input_state_t& cb)
  {
    m_inputStateCallback = cb;
  }

  ////
  // Terminal interface
  Console& LibRetro::getRootConsole(void)
  {
    return *m_rootConsole;
  }

  void LibRetro::shutdown() const
  {
    _environment(RETRO_ENVIRONMENT_SHUTDOWN, NULL);
  }

  bool LibRetro::isKeyDown(PlayerInput player, JoypadKeyInput key) const
  {
    int16_t val = _inputState(static_cast<unsigned>(player), RETRO_DEVICE_JOYPAD,
                              0, static_cast<unsigned>(key));
    return static_cast<bool>(val);
  }

  bool LibRetro::isKeyUp(PlayerInput player, JoypadKeyInput key) const
  {
    return !isKeyDown(player, key);
  }

  void LibRetro::addToCustomFont(const char32_t startingCodePoint,
                                 const unsigned width, const unsigned height,
                                 const unsigned char* const image)
  {
    m_rootConsole->addToCustomFont(startingCodePoint, width, height, image);
  }
  void LibRetro::addXBMToCustomFont(const char32_t startingCodePoint,
                                    const unsigned width, const unsigned height,
                                    const unsigned char* const image)
  {
    m_rootConsole->addXBMToCustomFont(startingCodePoint, width, height, image);
  }

  // Log
  void LibRetro::log(const LogLevel level, const std::string& msg) const
  {
    m_logCallback(static_cast<enum retro_log_level>(level), msg.c_str());
  }

  ////
  // Callback functions

  bool LibRetro::_environment(unsigned cmd, void *data) const
  {
    if (NULL != m_environmentCallback)
    {
      return m_environmentCallback(cmd, data);
    }
    else
    {
      return false;
    }
  }

  void LibRetro::_videoRefresh(const void *data, unsigned width, unsigned height, size_t pitch) const
  {
    if (NULL != m_videoRefreshCallback)
    {
      m_videoRefreshCallback(data, width, height, pitch);
    }
  }

  void LibRetro::_audioSample(int16_t left, int16_t right) const
  {
    if (NULL != m_audioSampleCallback)
    {
      m_audioSampleCallback(left, right);
    }
  }

  size_t LibRetro::_audioSampleBatch(const int16_t *data, size_t frames) const
  {
    if (NULL != m_audioSampleBatchCallback)
    {
      return m_audioSampleBatchCallback(data, frames);
    }
    else
    {
      return 0u;
    }
  }

  void LibRetro::_inputPoll(void) const
  {
    if (NULL != m_inputPollCallback)
    {
      m_inputPollCallback();
    }
  }

  int16_t LibRetro::_inputState(unsigned port, unsigned device, unsigned index, unsigned id) const
  {
    if (NULL != m_inputStateCallback)
    {
      return m_inputStateCallback(port, device, index, id);
    }
    else
    {
      return 0u;
    }
  }

  // This method is static because of the LibRetro interface
  void LibRetro::_timeCallback(retro_usec_t usec)
  {
    m_instance->m_deltaTime = usec / 1000000.0;
  }

}

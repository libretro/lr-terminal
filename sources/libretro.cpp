#include "libretro.h"
#include "terminal_retro.h"

extern "C"
{

  // Implementation of the libretro core functions

  // Setting the callbacks
  void retro_set_environment(retro_environment_t cb)
  {
    LRTerminal::LibRetro::getInstance().setEnvironment(cb);
  }

  void retro_set_video_refresh(retro_video_refresh_t cb)
  {
    LRTerminal::LibRetro::getInstance().setVideoRefresh(cb);
  }

  void retro_set_audio_sample(retro_audio_sample_t cb)
  {
    LRTerminal::LibRetro::getInstance().setAudioSample(cb);
  }

  void retro_set_audio_sample_batch(retro_audio_sample_batch_t cb)
  {
    LRTerminal::LibRetro::getInstance().setAudioSampleBatch(cb);
  }

  void retro_set_input_poll(retro_input_poll_t cb)
  {
    LRTerminal::LibRetro::getInstance().setInputPoll(cb);
  }

  void retro_set_input_state(retro_input_state_t cb)
  {
    LRTerminal::LibRetro::getInstance().setInputState(cb);
  }

  // Library global initialization.
  void retro_init(void)
  {
    LRTerminal::LibRetro::getInstance().init();
  }

  // Library global deinitialization.
  void retro_deinit(void)
  {
    LRTerminal::LibRetro::getInstance().deinit();
    LRTerminal::LibRetro::destroyInstance();
  }

  // API Version
  unsigned retro_api_version(void)
  {
    return RETRO_API_VERSION;
  }

  // System info
  void retro_get_system_info(struct retro_system_info *info)
  {
    LRTerminal::LibRetro::getInstance().getSystemInfo(info);
  }

  // System audio / video info. Called after retro_load_game()
  void retro_get_system_av_info(struct retro_system_av_info *info)
  {
    LRTerminal::LibRetro::getInstance().getSystemAudioVideoInfo(info);
  }

  // Sets device to be used for player 'port'.
  void retro_set_controller_port_device(unsigned port, unsigned device)
  {
    LRTerminal::LibRetro::getInstance().setControllerPortDevice(port, device);
  }

  // Resets the current game.
  void retro_reset(void)
  {
    LRTerminal::LibRetro::getInstance().resetGame();
  }


  // Runs the game for one video frame.
  void retro_run(void)
  {
    LRTerminal::LibRetro::getInstance().runGame();
  }

  // Returns the amount of data the implementation requires to serialize internal state (save states).
  size_t retro_serialize_size(void)
  {
    /* TODO */
    /* Unsupported for now */
    return 0u;
  }

  // Serializes internal state.
  bool retro_serialize(void *data, size_t size)
  {
    /* TODO */
    /* Unsupported for now */
    (void)data;
    (void)size;
    return false;
  }

  // Unserializes internal state.
  bool retro_unserialize(const void *data, size_t size)
  {
    /* TODO */
    /* Unsupported for now */
    (void)data;
    (void)size;
    return false;
  }

  // Cheats, not supported
  void retro_cheat_reset(void)
  {
    // Unsupported
  }

  void retro_cheat_set(unsigned index, bool enabled, const char *code)
  {
    // Unsupported
    (void)index;
    (void)enabled;
    (void)code;
  }

  // Loads a game.
  bool retro_load_game(const struct retro_game_info *game)
  {
    std::string path = "";
    if (game->path != NULL)
    {
      path = game->path;
    }
    return LRTerminal::LibRetro::getInstance().loadGame(path);
  }

  // Loads a "special" kind of game. Should not be used, except in extreme cases.
  bool retro_load_game_special(unsigned game_type, const struct retro_game_info *info, size_t num_info)
  {
    // Unsupported
    (void)game_type;
    (void)info;
    (void)num_info;
    return false;
  }

  // Unloads a currently loaded game.
  void retro_unload_game(void)
  {
    return LRTerminal::LibRetro::getInstance().unloadGame();
  }

  // Gets region of game.
  unsigned retro_get_region(void)
  {
    // Not relevant for this core
    return RETRO_REGION_PAL;
  }

  // Gets region of memory.
  void *retro_get_memory_data(unsigned id)
  {
    // Unsupported
    (void)id;
    return NULL;
  }

  size_t retro_get_memory_size(unsigned id)
  {
    // Unsupported
    (void)id;
    return 0u;
  }

}

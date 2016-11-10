
#ifndef _TERMINAL_RETRO__H_
#define _TERMINAL_RETRO__H_

#include "libretro.h"
#include "terminal_game.h"
#include "terminal_terminal.h"
#include "terminal_rootconsole.h"
#include "terminal_log.h"

namespace LRTerminal {

  // Main class
  class LibRetro: public Terminal
  {
  public:
    // The LibRetro is used as a singleton
    static LibRetro& getInstance(void);
    // Destructor for the singleton
    static void destroyInstance(void);

    // System info
    void getSystemInfo(struct retro_system_info *info) const;

    // Initialization
    void init();

    // Deinitialization
    void deinit();

    // System Audio & Video infos
    void getSystemAudioVideoInfo(struct retro_system_av_info *info) const;

    // Set the port and device of controllers
    void setControllerPortDevice(unsigned port, unsigned device);

    // Reset the game
    void resetGame(void);

    // Load a game
    bool loadGame(const std::string& path);

    // Unload a game
    void unloadGame(void);

    // Run one frame of the game
    void runGame(void);

    // Setters for callbacks
    void setEnvironment(retro_environment_t& cb);
    void setVideoRefresh(retro_video_refresh_t& cb);
    void setAudioSample(retro_audio_sample_t& cb);
    void setAudioSampleBatch(retro_audio_sample_batch_t& cb);
    void setInputPoll(retro_input_poll_t& cb);
    void setInputState(retro_input_state_t& cb);

    ////
    // Inherited from the Terminal interface
    // Get the Root Console
    virtual Console& getRootConsole(void);
    // Shutdown
    virtual void shutdown() const;
    // Input
    virtual bool isKeyDown(PlayerInput player, JoypadKeyInput key) const;
    virtual bool isKeyUp(PlayerInput player, JoypadKeyInput key) const;
    // Custom font
    virtual void addToCustomFont(const char32_t startingCodePoint,
                                 const unsigned width, const unsigned height,
                                 const unsigned char* const image);
    virtual void addXBMToCustomFont(const char32_t startingCodePoint,
                                    const unsigned width, const unsigned height,
                                    const unsigned char* const image);

    // For the log interface
    void log(const LogLevel level, const std::string& msg) const;
  private:
    /* Constructor */
    LibRetro(void);
    /* Destructor */
    ~LibRetro(void);

    /* Copy constructor is declared but not implemented */
    LibRetro(const LibRetro& that);
    /* Operator = is declared but not implemented */
    LibRetro& operator=(const LibRetro& that);

    /* Environment
     * Gives implementations a way of performing uncommon tasks.
     */
    bool _environment(unsigned cmd, void *data) const;

    /* Video Refresh
     * Render a frame.
     *
     * Width and height specify dimensions of buffer.
     * Pitch specifices length in bytes between two lines in buffer.
     *
     * For performance reasons, it is highly recommended to have a frame
     * that is packed in memory, i.e. pitch == width * byte_per_pixel.
     * Certain graphic APIs, such as OpenGL ES, do not like textures
     * that are not packed in memory.
     */
    void _videoRefresh(const void *data, unsigned width, unsigned height, size_t pitch) const;

    /* Renders a single audio frame. Should only be used if implementation
     * generates a single sample at a time.
     * Format is signed 16-bit native endian.
     */
    void _audioSample(int16_t left, int16_t right) const;

    /* Renders multiple audio frames in one go.
     *
     * One frame is defined as a sample of left and right channels, interleaved.
     * I.e. int16_t buf[4] = { l, r, l, r }; would be 2 frames.
     * Only one of the audio callbacks must ever be used.
     */
    size_t _audioSampleBatch(const int16_t *data, size_t frames) const;

    /* Polls input.
     */
    void _inputPoll(void) const;

    /* Queries for input for player 'port'. device will be masked with
     * RETRO_DEVICE_MASK.
     *
     * Specialization of devices such as RETRO_DEVICE_JOYPAD_MULTITAP that
     * have been set with retro_set_controller_port_device()
     * will still use the higher level RETRO_DEVICE_JOYPAD to request input.
     */
    int16_t _inputState(unsigned port, unsigned device, unsigned index, unsigned id) const;

    /* LibRetro instance */
    static LibRetro* m_instance;

    /* Time callback */
    static void _timeCallback(retro_usec_t usec);

    /* Game instance */
    GameInterface& m_game;

    /* Root Console */
    RootConsole* m_rootConsole;

    /* Callbacks */
    /* Environment */
    retro_environment_t m_environmentCallback;
    /* Video refresh */
    retro_video_refresh_t m_videoRefreshCallback;
    /* Audio sample */
    retro_audio_sample_t m_audioSampleCallback;
    /* Audio sample batch */
    retro_audio_sample_batch_t m_audioSampleBatchCallback;
    /* Input polling */
    retro_input_poll_t m_inputPollCallback;
    /* Input state */
    retro_input_state_t m_inputStateCallback;
    /* Others, those are obtained by asking the environment */
    /* Log callback */
    retro_log_printf_t m_logCallback;
    // TODO

    /* Other environment infos */
    /* Boolean indicating if frames can be dropped if there are no changes */
    bool m_canDupe;

    /* Delta time since last runGame call */
    double m_deltaTime;

    /* Supports running without game ? */
    bool m_supportNoGame;
    /* Library name */
    std::string m_libraryName;
    /* Library version */
    std::string m_libraryVersion;
    /* Valid extensions */
    std::string m_validExtensions;
  };

}

#endif

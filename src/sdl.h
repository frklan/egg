#pragma once
#include <SDL.h>
#include <SDL_mixer.h>

#include "airplane.h"


namespace yellowfortyfourcom {
  struct sdl_deleter {
      void operator()(Mix_Chunk* p) noexcept { Mix_FreeChunk(p); }
      void operator()(SDL_RWops *p) noexcept { SDL_RWclose(p); }
  };


  class SDL {
    public:
      SDL();
      ~SDL();
      void loadSoundfromFile(std::string filename);
      void play(bool playAsync = false);

    private:
      std::unique_ptr<Mix_Chunk, sdl_deleter> sound;
  };

  class SdlException : public std::exception {};
  class SdlInitException : public SdlException {};
  class SdlMixerException : public SdlException {};
  class SdlMixerInitException : public SdlMixerException {};
  class SdlMixerSoundLoadException : public SdlMixerException {};

}
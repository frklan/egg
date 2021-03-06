#include <iostream>
#include <vector>
#include <memory>
#include <SDL.h>
#include <SDL_mixer.h>
#include <exception>

#include "sdl.h"

namespace yellowfortyfourcom {

  SDL::SDL() {
    auto iRet = SDL_Init(SDL_INIT_AUDIO);
    if(iRet < 0) {
      throw SdlInitException(); 
    }
    auto mRet = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    if(mRet < 0) {
      throw SdlMixerInitException();
    }
    
    auto soundRaw =  std::unique_ptr<SDL_RWops, sdl_deleter>(SDL_RWFromConstMem(airplane_chime_x_wav.data(), airplane_chime_x_wav.size()));
    sound = std::unique_ptr<Mix_Chunk, sdl_deleter>(Mix_LoadWAV_RW(soundRaw.get(), 0));
  }

  SDL::~SDL() {
    Mix_Quit();  
    SDL_Quit();
  }

  void SDL::loadSoundfromFile(std::string filename) {

    // We'll try to load new sound from disk..
    auto newSound = std::unique_ptr<Mix_Chunk, sdl_deleter>(Mix_LoadWAV(filename.c_str()));
    if(newSound == nullptr) {
      throw SdlMixerSoundLoadException();
    }
    // it worked, let's mode it into our object variable.
    sound = std::move(newSound);
  }

  void SDL::play(bool playAsync) {
    Mix_PlayChannel(-1, sound.get(), 0);

    if(!playAsync) {
      while(Mix_PlayingMusic() || Mix_Playing(-1)) {
        SDL_Delay(10);
      }
    }
  }
}
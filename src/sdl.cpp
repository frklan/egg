#include <iostream>
#include <vector>
#include <memory>
#include <SDL.h>
#include <SDL_mixer.h>
#include <exception>

#include "sdl.h"

namespace yellowfortyfourcom {

  SDL::SDL() {
    auto iRet = SDL_Init(SDL_INIT_AUDIO) ;
    auto oRet = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    if(iRet < 0 || oRet < 0) {
      throw std::runtime_error("SDL init error: " + std::string(SDL_GetError())) ;
    }
    
    auto soundRaw =  std::unique_ptr<SDL_RWops, sdl_deleter>(SDL_RWFromConstMem(airplane_chime_x_wav.data(), airplane_chime_x_wav.size()));
    sound = std::unique_ptr<Mix_Chunk, sdl_deleter>(Mix_LoadWAV_RW(soundRaw.get(), 0));
  }

  SDL::~SDL() {
    Mix_Quit();  
    SDL_Quit();
  }

  void SDL::loadChunkEffect(std::string filename) {
    sound = std::unique_ptr<Mix_Chunk, sdl_deleter>(Mix_LoadWAV(filename.c_str()));
    if(sound == nullptr) {
      std::cout << "error ,oading file:" << SDL_GetError() << std::endl;
    }
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
#!/bin/bash

clang++ -std=c++1z -g -Wall src/app.cpp src/timer.cpp src/sdl.cpp src/main.cpp -o egg \
  -I /usr/local/include -L /usr/local/lib \
  -I$(brew --prefix boost)/include -L$(brew --prefix boost)/lib \
  -lboost_program_options \
  -I /Library/Frameworks/SDL2.framework/Headers \
  -I /Library/Frameworks/SDL2_mixer.framework/Headers \
  -framework SDL2  -framework SDL2_mixer
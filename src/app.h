#pragma once

#include <iostream>
#include <memory>
#include <sstream>
#include <ctime>

#include "timer.h"
#include "sdl.h"


namespace yellowfortyfourcom {
  
  const std::string APP_VERSION = "v0.3.0";

  class App {
    public:
      App() = delete;
      App(int arvc, char** argv);

      int run();

    private:
      void parseCmdOptions(int argc, char** argv);
      std::time_t getAlarmTimeFromRelativeString(const std::string& timeString);
      std::time_t getAlarmTimeFromAbsoluteString(const std::string& timeString);
      bool checkSoundFileExist(std::string soundFile);

      std::unique_ptr<std::tm> getCurrentTime();
      void timesUp();
      
      std::unique_ptr<SDL> sdl;
      std::string time;
      bool doRelativeTime = false;
      bool doPlaySound = true;
      bool doCustomSound = false;
      std::string soundFile;
  };
}
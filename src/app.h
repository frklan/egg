#pragma once

#include <iostream>
#include <memory>
#include <sstream>
#include <ctime>

#include "timer.h"


namespace yellowfortyfourcom {
  
  const std::string APP_VERSION = "v0.1.0";

  class App {
    public:
      App() = delete;
      App(int arvc, char** argv);

      int run();

    private:
      void parseCmdOptions(int argc, char** argv);
      std::unique_ptr<std::tm> getCurrentTime();
      void timesUp();

      std::unique_ptr<yellowfortyfourcom::Timer> timer;
  };
}
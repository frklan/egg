#pragma once

#include <iostream>
#include <memory>
#include <sstream>
#include <ctime>

#include "timer.h"


namespace yellowfortyfourcom {
  class App {
    public:
      App() = delete;
      App(int arvc, char** argv);

      int run();

    private:
      void parseCmdOptions(int argc, char** argv);
      std::unique_ptr<std::tm> getCurrentTime();

      std::unique_ptr<yellowfortyfourcom::Timer> timer;
  };
}
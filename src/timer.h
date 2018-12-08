#pragma once 
#include <iostream>
#include <ctime>

namespace yellowfortyfourcom {
  class Timer {
    public:
      Timer() = delete;
      Timer(std::tm& alarmTime);

      int run();

    private:
      std::unique_ptr<std::tm> getCurrentTime();
      
      std::tm alarmTime;
  };
}
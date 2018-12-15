#pragma once 
#include <iostream>
#include <ctime>

namespace yellowfortyfourcom {
  class Timer {
    public:
      Timer() = delete;
      Timer(std::time_t& alarmTime, std::function<void(const std::time_t&)> = [](std::time_t t) {});

      int run();

    private:
      std::time_t getCurrentTime();
      std::function<void(std::time_t&)> cb;
      std::time_t alarmTime;
  };
}
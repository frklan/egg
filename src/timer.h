#pragma once 
#include <iostream>
#include <ctime>

namespace yellowfortyfourcom {
  class Timer {
    public:
      Timer() = delete;
      Timer(std::tm& alarmTime, std::function<void(const std::tm&)> = [](std::tm t) {});

      int run();

    private:
      std::unique_ptr<std::tm> getCurrentTime();
      std::function<void(std::tm)> cb;
      std::tm alarmTime;
  };
}
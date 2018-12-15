#include <iostream>
#include <iomanip>
#include <ctime>
#include <thread>

#include "timer.h"

namespace yellowfortyfourcom {
  using namespace std::chrono_literals;

  Timer::Timer(std::time_t& at, std::function<void(const std::time_t&)> callBack) : 
  cb(callBack),
  alarmTime(at)
  { 
    //std::cout << "Timer created: " << alarmTime.tm_hour << ":" << alarmTime.tm_min << std::endl;
  }

  int Timer::run() {
    while(1) {
      auto now = getCurrentTime();
      
      if(alarmTime <= now) {
        std::cout << '\r' << std::flush;
        cb(alarmTime);
        break;
      } else {
      std::cout << '\r' 
        << std::put_time(std::localtime(&now), "%H:%M:%S")  
        << std::flush;
        std::this_thread::sleep_for(500ms);
      }
    }
    std::cout << std::endl;
    return 0;
  }

  std::time_t Timer::getCurrentTime() {
    using sec = std::chrono::duration<int, std::ratio<1>>;
    auto now = std::chrono::time_point_cast<sec>(std::chrono::system_clock::now()).time_since_epoch();
   
    return now.count();
  }
}
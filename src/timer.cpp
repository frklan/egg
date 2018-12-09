#include <iostream>
#include <iomanip>
#include <ctime>
#include <thread>

#include "timer.h"

namespace yellowfortyfourcom {
  using namespace std::chrono_literals;

  Timer::Timer(std::tm& at, std::function<void(const std::tm&)> callBack) : 
  cb(callBack),
  alarmTime(at)
  { 
    //std::cout << "Timer created: " << alarmTime.tm_hour << ":" << alarmTime.tm_min << std::endl;
  }

  int Timer::run() {
    while(1) {
      auto now = getCurrentTime();
      
      if(alarmTime.tm_hour <= now->tm_hour && alarmTime.tm_min <= now->tm_min && alarmTime.tm_sec <= now->tm_sec) {
        std::cout << '\r' << std::flush;
        cb(alarmTime);
        break;
      } else {
      std::cout << '\r' 
        << std::setfill('0') << std::setw(2) << now->tm_hour 
        << ":" 
        << std::setfill('0') << std::setw(2) << now->tm_min 
        << ":" 
        << std::setfill('0') << std::setw(2) << now->tm_sec 
        << std::flush;
        std::this_thread::sleep_for(500ms);
      }
    }
    std::cout << std::endl;
    return 0;
  }

  std::unique_ptr<std::tm> Timer::getCurrentTime() {
    auto now = std::make_unique<std::tm>();
    auto t = std::time(0); 
    auto l = std::localtime(&t);
    now->tm_sec = l->tm_sec;
    now->tm_min = l->tm_min;
    now->tm_hour = l->tm_hour;
    now->tm_mday = l->tm_mday;
    now->tm_mon  = l->tm_mon;
    now->tm_year = l->tm_year; 
    now->tm_wday = l->tm_wday;
    now->tm_yday = l->tm_yday;
    now->tm_isdst = l->tm_isdst;
    return now;
  }
}
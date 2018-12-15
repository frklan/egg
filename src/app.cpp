#include <iostream>
#include <chrono>
#include <ctime>
#include <memory>
#include <thread>
#include <sstream>
#include <iomanip>
#include <string>
#include <exception>
#include <regex>

#include "boost/program_options.hpp"
#include "app.h"
#include "sdl.h"

namespace yellowfortyfourcom {

  App::App(int argc, char** argv) {
    std::string time;

    // Define and parse the program options  
    namespace po = boost::program_options; 
    po::options_description desc("Options"); 
    desc.add_options() 
      ("help", "Print help messages")
      ("version,v", "show version")
      (",r", "use relative time")
      ("time", po::value<std::string>(&time)->required(), "alarm time");
    
    po::positional_options_description positionalOptions; 
    positionalOptions.add("time", 1); 

    po::variables_map vm; 
    try { 
      po::store(po::command_line_parser(argc, argv).options(desc).positional(positionalOptions).run(), vm);

      if(vm.count("help")) { 
        std::cout << "Usage:\n\tegg [options] [time]\n" << std::endl << desc << std::endl; 
        exit(0); 
      } 
      if(vm.count("version")) {
        std::cout << "egg " << APP_VERSION << " (C) 2018 Fredrik Andersson" << std::endl;
        exit(0);
      }
      po::notify(vm); // throws on error, so do after help in case there are any problems 

      std::time_t alarmTime;
      if(vm.count("-r")) {
        alarmTime = getAlarmTimeFromRelativeString(time);    
      } else {
        alarmTime = getAlarmTimeFromAbsoluteString(time);
      }
      timer = std::make_unique<yellowfortyfourcom::Timer>(alarmTime, [this](const std::time_t){ timesUp(); });

    } catch(po::error& e) { 
      std::cerr << "ERROR: " << e.what() << std::endl << std::endl; 
      std::cerr << desc << std::endl;
      exit(-1);
    } 
  }

  std::time_t App::getAlarmTimeFromAbsoluteString(const std::string& timeString) {
    std::regex hhmmss("^((?:[0-1][0-9])|(?:[2][0-3])):([0-5][0-9]):([0-5][0-9])$"); // HH:MM:SS
    std::smatch match;
    
    if(regex_match(timeString, match, hhmmss)) {
      auto h = std::chrono::hours(atoi(match[1].str().c_str()));
      auto mm = std::chrono::minutes(atoi(match[2].str().c_str()));
      auto s = std::chrono::seconds(atoi(match[3].str().c_str()));
        
      using days = std::chrono::duration<int, std::ratio<86400>>;
      auto midnight = std::chrono::time_point_cast<days>(std::chrono::system_clock::now()).time_since_epoch();

      auto alarmTime = midnight + h + mm + s;
      
      // alarm is now in local time, we need to "cast" it to GMT
      std::time_t a = alarmTime.count();
      auto gmt = std::gmtime(&a);
      
      // now return it as time_t
      return mktime(gmt);
    }
    throw new std::runtime_error("Invalid time");
  }

  std::time_t App::getAlarmTimeFromRelativeString(const std::string& timeString) {
    std::regex hhmmss("^([0-9]*):([0-5][0-9]):([0-5][0-9])$"); // HHH:MM:SS
    std::regex mmss("^([0-9]*):([0-5][0-9])$"); // MM:SS
    std::regex ss ("^([0-9]*)$"); // SS

    std::string fmt;
    std::smatch match;
    auto h = std::chrono::hours(0);
    auto mm = std::chrono::minutes(0);
    auto s = std::chrono::seconds(0);
    
    if(regex_match(timeString, match, hhmmss)) {
      h = std::chrono::hours(atoi(match[1].str().c_str()));
      mm = std::chrono::minutes(atoi(match[2].str().c_str()));
      s = std::chrono::seconds(atoi(match[3].str().c_str()));
    } else if(regex_match(timeString, match, mmss)) {
      mm = std::chrono::minutes(atoi(match[1].str().c_str()));
      s = std::chrono::seconds(atoi(match[2].str().c_str()));
    } else if(regex_match(timeString, match, ss)) {
      s = std::chrono::seconds(atoi(match[1].str().c_str()));
    } else {
      std::cerr << "invalid input!" << std::endl;
      exit(-1);
    }  
    std::chrono::duration<long long> alarmOffset = h + mm + s;

    return std::chrono::system_clock::to_time_t(std::chrono::system_clock::now() + alarmOffset);
  }

  void App::timesUp() {
    std::cout << "\rTime's up!\n";
    
    try { 
      yellowfortyfourcom::SDL sdl{};
      sdl.play();
    } catch(std::exception& e) {
      std::cerr << e.what();
    }
  }

  int App::run() {
    return timer->run();
  }
}
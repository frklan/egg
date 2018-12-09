#include <iostream>
#include <chrono>
#include <ctime>
#include <memory>
#include <thread>
#include <sstream>
#include <iomanip>
#include <string>
#include <exception>

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

      std::tm t;
      std::stringstream inputtime(time);
      inputtime >> std::get_time(&t, "%H:%M:%S");
      
      timer = std::make_unique<yellowfortyfourcom::Timer>(t, [this](const std::tm){ timesUp(); });

    } catch(po::error& e) { 
      std::cerr << "ERROR: " << e.what() << std::endl << std::endl; 
      std::cerr << desc << std::endl;
      exit(-1);
    } 
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
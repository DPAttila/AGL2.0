#ifndef UTIL_CPP
#define UTIL_CPP

#include "util.h"

#include <iostream>

namespace agl {
  void alert(std::string message) {
    std::cout << STDOUT_RED << "Error:\n" << message << STDOUT_END_COLOR << "\n\n";
  }
  
  void log(std::string message) {
    std::cout << message << "\n";
  }
}
#endif

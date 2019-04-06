#ifndef UTIL_CPP
#define UTIL_CPP

#include "Util.h"

#include <iostream>

namespace agl {
  void alert(std::string message) {
    std::cout << STDOUT_RED << message << STDOUT_END_COLOR << "\n";
  }
}
#endif

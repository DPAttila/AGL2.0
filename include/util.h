#ifndef UTIL_H
#define UTIL_H

#include <string>

namespace agl {
  const std::string STDOUT_RED = "\033[0;31m";
  const std::string STDOUT_END_COLOR = "\033[0;m";
  
  /**
   * Writes an alert to stdout
   */
  void alert(std::string message);
  
  /**
   * Logs info to stdout
   */
  void log(std::string log);
}

#endif

#pragma once

#include <chrono>
#include <string>
#include "logger.h"

using time_stamp = std::chrono::time_point<std::chrono::system_clock,
                                           std::chrono::microseconds>;

class Timer {
private:
  static std::string name;
  static time_stamp time;

public:
  static void start(std::string timerName);
  static void stop();
};

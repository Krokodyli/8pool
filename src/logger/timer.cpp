#include "timer.h"

std::string Timer::name = "";
time_stamp Timer::time =
    std::chrono::time_point_cast<std::chrono::microseconds>(
        std::chrono::high_resolution_clock::now());

void Timer::start(std::string timerName) {
  Timer::name = timerName;
  time = std::chrono::time_point_cast<std::chrono::microseconds>(
      std::chrono::high_resolution_clock::now());
}

void Timer::stop() {
  time_stamp end = std::chrono::time_point_cast<std::chrono::microseconds>(
      std::chrono::high_resolution_clock::now());
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - time);
  Logger::log(Timer::name + ": " +
              std::to_string((double)duration.count() / 1000.0));
}

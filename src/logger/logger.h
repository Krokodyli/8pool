#pragma once

#include <string>
#include <iostream>

enum class LogType {
  info,
  error,
  criticalError
};

class Logger {
private:
  static int verboseLevel;

public:
  static void log(std::string message, LogType logType = LogType::info);
  static void logError(std::string message);
  static void logCriticalError(std::string message);
};

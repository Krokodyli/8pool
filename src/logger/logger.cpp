#include "logger.h"

int Logger::verboseLevel = 3;

void Logger::log(std::string message, LogType logType) {
  switch(logType) {
  case LogType::info:
    if(verboseLevel >= 3)
      std::cout << "INFO: " << message << std::endl;
    break;
  case LogType::error:
    if (verboseLevel >= 2)
      std::cout << "ERROR: " << message << std::endl;
    break;
  case LogType::criticalError:
    if (verboseLevel >= 1)
      std::cout << "CRITICAL ERROR: " << message << std::endl;
    throw std::runtime_error(message);
    break;
  }
}

void Logger::logError(std::string message) {
  Logger::log(message, LogType::error);
}

void Logger::logCriticalError(std::string message) {
  Logger::log(message, LogType::criticalError);
}

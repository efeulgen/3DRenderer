
#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <ctime>

enum LogType
{
      LOG_INFO,
      LOG_WARNING,
      LOG_ERROR
};

struct LogEntry
{
      LogType type;
      std::string message;
};

class Logger
{
public:
      static std::vector<LogEntry> entries;
      static void Log(const std::string &message);
      static void Err(const std::string &message);
};

#endif

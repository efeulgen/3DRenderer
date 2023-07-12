
#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>

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
      static std::vector<LogEntry> entries;
      static void Logg(const std::string &message);
      static void Err(const std::string &message);
};

#endif

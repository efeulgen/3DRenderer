
#include "Logger.h"

std::vector<LogEntry> Logger::entries;

std::string CurrentDateTimeToString()
{
      std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

      std::string output(30, '\0');
      std::strftime(&output[0], output.size(), "%d-%b-%Y %H:%M:%S", std::localtime(&now));
      return output;
}

void Logger::Log(const std::string &message)
{
      LogEntry entry;
      entry.type = LOG_INFO;
      entry.message = "LOG: [" + CurrentDateTimeToString() + "]: " + message;

      std::cout << "\x1B[32m" << entry.message << "\033[0m" << std::endl;
      entries.push_back(entry);
}

void Logger::Log(const std::string &message, int num)
{
      LogEntry entry;
      entry.type = LOG_INFO;
      entry.message = "LOG: [" + CurrentDateTimeToString() + "]: " + message;

      std::cout << "\x1B[32m" << entry.message << num << "\033[0m" << std::endl;
      entries.push_back(entry);
}

void Logger::Warn(const std::string &message)
{
      LogEntry entry;
      entry.type = LOG_WARNING;

      entry.message = "WARN: [" + CurrentDateTimeToString() + "]: " + message;

      std::cout << "\033[33m" << entry.message << "\033[0m" << std::endl;
      entries.push_back(entry);
}

void Logger::Err(const std::string &message)
{
      LogEntry entry;
      entry.type = LOG_ERROR;
      entry.message = "ERR: [" + CurrentDateTimeToString() + "]: " + message;

      std::cout << "\x1B[91m" << entry.message << "\033[0m" << std::endl;
      entries.push_back(entry);
}

void Logger::Err(const std::string &message, int num)
{
      LogEntry entry;
      entry.type = LOG_ERROR;
      entry.message = "ERR: [" + CurrentDateTimeToString() + "]: " + message;

      std::cout << "\x1B[91m" << entry.message << num << "\033[0m" << std::endl;
      entries.push_back(entry);
}

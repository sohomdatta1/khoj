#pragma once

#include <chrono>
#include <iostream>
#include <vector>

class Entry {
public:
  std::string time;
  std::string msg;
  Entry(std::string time, std::string msg);
};

class Logger {
private:
  std::vector<Entry> log_store;
  const std::chrono::steady_clock::time_point start =
      std::chrono::steady_clock::now();
  static Logger *instance;
  Logger();

public:
  void write_log();
  static Logger *getInstance();
  void log(std::string text);
  std::string getTime();
};

#include "logger.hh"

Logger *Logger::instance = NULL;

Entry::Entry(std::string time, std::string msg) {
  this->time = time;
  this->msg = msg;
}

Logger::Logger() { log_store.push_back(Entry(getTime(), "Starting logger")); }

Logger *Logger::getInstance() {
  if (!instance) {
    instance = new Logger();
  }

  return instance;
}

void Logger::write_log() {
  for (int i = 0; i < log_store.size(); i++) {
    std::cout << "\u001b[33m"
              << "[khoj " << log_store[i].time
              << "]\u001b[0m: " << log_store[i].msg << std::endl;
  }
}

std::string Logger::getTime() {
  return std::to_string(
             ((std::chrono::duration<double>)(std::chrono::steady_clock::now() -
                                              this->start))
                 .count()) +
         "secs";
}

void Logger::log(std::string text) {
  log_store.push_back(Entry(getTime(), text));
}

#include "indexer.hh"
#include "indexUtils.hh"
#include "logger.hh"
#include <iostream>
#include <functional>

void show_help() {
  std::cout << "khoj requires at least one parameter to run\n";
}

int main(int argc, char **argv) {
  Logger *logger = Logger::getInstance();
  if (argc != 2) {
    show_help();
    return -1;
  }
  std::cout << "Yo!" << std::endl;
  logger->log("Actual program starts");

  IndexUtils::FileStore fileStore;
  IndexUtils::IndexStore indexStore;
  IndexUtils::MainTrigramTracker mainTrigramTracker;
  IndexUtils::PerFileTrigramStore perFileTrigramStore;
  Indexer indexProcess(fileStore, perFileTrigramStore, mainTrigramTracker, indexStore);
  indexProcess.indexDir(argv[1]);
  logger->write_log();
  return 0;
}

#include "indexUtils.hh"
#include "indexer.hh"
#include "logger.hh"
#include <functional>
#include <iostream>
#include <memory>

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

  std::shared_ptr<IndexUtils::FileStore> fileStore =
      std::make_shared<IndexUtils::FileStore>();
  std::shared_ptr<IndexUtils::IndexStore> indexStore =
      std::make_shared<IndexUtils::IndexStore>();
  std::shared_ptr<IndexUtils::MainTrigramTracker> mainTrigramTracker =
      std::make_shared<IndexUtils::MainTrigramTracker>();
  std::shared_ptr<IndexUtils::PerFileTrigramStore> perFileTrigramStore =
      std::make_shared<IndexUtils::PerFileTrigramStore>();
  Indexer indexProcess(fileStore, perFileTrigramStore, mainTrigramTracker,
                       indexStore);
  indexProcess.indexDir(argv[1]);
  logger->write_log();
  return 0;
}

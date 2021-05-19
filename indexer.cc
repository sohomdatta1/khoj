#include "indexer.hh"
#include "logger.hh"
#include "walkDir.hh"

Indexer::Indexer(IndexUtils::FileStore fileStore,
                 IndexUtils::PerFileTrigramStore perFileTrigramStore,
                 IndexUtils::MainTrigramTracker mainTrigramTracker,
                 IndexUtils::IndexStore indexStore) {
  this->fileStore = fileStore;
  this->perFileTrigramStore = perFileTrigramStore;
  this->mainTrigramTracker = mainTrigramTracker;
  this->indexStore = indexStore;
}

void Indexer::populateMainIndex(unsigned int trigram) { mainTrigramTracker.set(trigram); }

void Indexer::indexFile(std::string filePath) {
  // @todo: figure out utf-8
  // we should be able to do something with unsigned double
  std::ifstream filestream(filePath, std::fstream::binary);
  fileStore.registerFile(filePath);
  std::string data = "";
  unsigned int trigram;
  int n = 0;
  do {
    std::getline(filestream, data);
    const char *line = data.c_str();
    n = data.size();
    if (n > 2048) {
      (Logger::getInstance())
          ->log("Didn't index " + filePath +
                " since line size was over 2048 bytes (" + std::to_string(n) +
                " bytes).");
      return;
    }
    for (int i = 0; i < n - 2; i++) {
      if (line[i] == '\x00') {
        (Logger::getInstance())
            ->log("Didn't index " + filePath +
                  " since we suspect it to be a binary file (contains a null "
                  "character).");
        perFileTrigramStore.clear();
        return;
      }
      trigram = (line[i + 2] << 16 | line[i + 1] << 8 | line[i]) &
                0xFFFFFF; // Bad stuff, mangling for utf-8 is a certainity
      perFileTrigramStore.addElem(trigram);
    }
  } while (!filestream.eof());

  filestream.close();
  perFileTrigramStore.clearAndIterate(std::bind(&Indexer::populateMainIndex, this, std::placeholders::_1));
}

void Indexer::indexDir(std::string directory) {
  walkDir(directory, std::bind(&Indexer::indexFile, this, std::placeholders::_1));
}


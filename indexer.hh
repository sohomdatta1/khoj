#pragma once
#include "indexUtils.hh"
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

class Indexer {
private:
  IndexUtils::FileStore fileStore;
  IndexUtils::PerFileTrigramStore perFileTrigramStore;
  IndexUtils::MainTrigramTracker mainTrigramTracker;
  IndexUtils::IndexStore indexStore;
public:
  Indexer(IndexUtils::FileStore fileStore,
          IndexUtils::PerFileTrigramStore perFileTrigramStore,
          IndexUtils::MainTrigramTracker mainTrigramTracker,
          IndexUtils::IndexStore indexStore);
  void populateMainIndex(unsigned int);
  void indexFile(std::string);
  void indexDir(std::string);
};

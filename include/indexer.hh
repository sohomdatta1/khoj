#pragma once
#include "indexUtils.hh"
#include <iostream>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

class Indexer {
private:
  std::shared_ptr<IndexUtils::FileStore> fileStore;
  std::shared_ptr<IndexUtils::PerFileTrigramStore> perFileTrigramStore;
  std::shared_ptr<IndexUtils::MainTrigramTracker> mainTrigramTracker;
  std::shared_ptr<IndexUtils::IndexStore> indexStore;

public:
  Indexer(std::shared_ptr<IndexUtils::FileStore> fileStore,
          std::shared_ptr<IndexUtils::PerFileTrigramStore> perFileTrigramStore,
          std::shared_ptr<IndexUtils::MainTrigramTracker> mainTrigramTracker,
          std::shared_ptr<IndexUtils::IndexStore> indexStore);
  void populateMainIndex(unsigned int);
  void indexFile(std::string);
  void indexDir(std::string);
};

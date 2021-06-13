#include "indexUtils.hh"
#include "logger.hh"

int IndexUtils::FileStore::registerFile(std::string filePath) {
  fileList.push_back(filePath);
  return ++fileListTop;
}

IndexUtils::PerFileTrigramStore::PerFileTrigramStore() {
  store = std::make_unique<unsigned int []>(TRIGRAM_LIMIT);
  lookup_array = std::make_unique<unsigned int []>(TRIGRAM_LIMIT);
}

void IndexUtils::PerFileTrigramStore::addElem(unsigned int trigram) {
  if (!isSet(trigram)) {
    lookup_array[trigram] = top;
    store[top++] = trigram;
    top++;
  }
}

bool IndexUtils::PerFileTrigramStore::isSet(unsigned int trigram) {
  return top > lookup_array[trigram] && store[lookup_array[trigram]] == trigram;
}

void IndexUtils::PerFileTrigramStore::clearAndIterate(std::function<void(unsigned int)> callback) {
  while (top != 0) {
    callback(store[top--]);
  }
}

void IndexUtils::PerFileTrigramStore::clear() { top = 0; }

void IndexUtils::MainTrigramTracker::set(unsigned int trigram) {
  trigram_lookup[trigram] = 1;
}

bool IndexUtils::MainTrigramTracker::isSet(unsigned int trigram) {
  return (bool)trigram_lookup[trigram];
}

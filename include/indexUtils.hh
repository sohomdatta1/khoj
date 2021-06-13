
#pragma once
#include <bitset>
#include <vector>
#include <functional>
#include <memory>

namespace IndexUtils {
static const unsigned int TRIGRAM_LIMIT = 16777215;
class FileStore {
private:
  int fileListTop;
  std::vector<std::string> fileList;

public:
  FileStore() { fileList.reserve(4096); }
  int registerFile(std::string filePath);
};

class PerFileTrigramStore {
private:
  unsigned int top;
  // We need something (datastructure) that has O(1) everything... Like
  // literally O(1) everything... Anything other than that spirals out of
  // control really fast since that operation needs to be done for every byte in
  // the file. So the concept is simple... Combine the power of a stack and a
  // bit vector... One array is a stack that stores the elements and another is
  // a kind of a bit vector that stores the address of the element in the stack
  std::shared_ptr<unsigned int []> store;
  std::shared_ptr<unsigned int []> lookup_array;

public:
  PerFileTrigramStore();
  void addElem(unsigned int trigram);
  bool isSet(unsigned int trigram);
  void clear();
  void clearAndIterate(std::function<void(unsigned int)>);
};

class MainTrigramTracker {
private:
  std::bitset<TRIGRAM_LIMIT> trigram_lookup;

public:
  void set(unsigned int trigram);
  bool isSet(unsigned int trigram);
};

class IndexStore {
  private:
    int file_name;
  public:
};
} // namespace IndexUtils

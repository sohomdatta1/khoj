#include "walkDir.hh"
#include "logger.hh"

namespace fs = std::filesystem;

#if defined(WIN32) || defined(_WIN32)
#define PATH_SEPARATOR '\\'
#else
#define PATH_SEPARATOR '/'
#endif

const std::vector<std::string> forbidden_files{"node_modules", "vendor"};

bool checkDirectory(std::string directory) {
  const int last_pos = directory.find_last_of(PATH_SEPARATOR);
  std::string directory_part = directory.substr(last_pos + 1);
  if (directory_part.at(0) == '.' ||
      directory_part.at(directory_part.size() - 1) == '~') {
    return false;
  }

  for (long unsigned int i = 0; i < forbidden_files.size(); i++) {
    if (directory_part.compare(forbidden_files[i]) == 0) {
      return false;
    }
  }

  return true;
}

void walkDir(std::string directory, std::function<void(std::string)> callback) {
  int c = 0;
  auto options = fs::directory_options::skip_permission_denied;
  for (auto dirent = fs::recursive_directory_iterator(directory, options);
       dirent != fs::recursive_directory_iterator(); dirent++) {
    const std::string filePath = dirent->path();
    if (!checkDirectory(filePath)) {
      dirent.disable_recursion_pending();
      continue;
    }

    if (dirent->is_directory() || dirent->is_symlink()) {
      continue;
    }
    c++;
    callback(filePath);
  }
  (Logger::getInstance())
      ->log("Finished indexing " + std::to_string(c) + " files.");
}

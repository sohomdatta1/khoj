#include <ctime>
#include <string>
#include <unordered_map>
#include <vector>

namespace Config {
typedef enum file_settings {
  USER_FORBIDDEN_FILES,
  USER_ALLOWED_FILES,
  SPECIFIC_FILES_THAT_ARE_ALLOWED,
  SPECIFIC_FILES_THAT_ARE_FORBIDDEN
} file_settings;

class ConfigStore {
private:
  std::vector<std::string> user_forbidden_files;
  std::vector<std::string> user_allowed_files;
  std::vector<std::string> specific_files_that_are_forbidden;
  std::vector<std::string> specific_files_that_are_allowed;
  std::unordered_map<std::string, std::string> misc_store;
  std::string settings_file_name;

public:
  ConfigStore();
  ConfigStore(std::string filename);
  std::vector<std::string> getFileSetting(file_settings setting_type);
  std::string getSetting(std::string setting_name);
  void dumpConfig();
};
} // namespace Config

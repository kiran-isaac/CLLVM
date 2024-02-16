#include <args.h>
#include <filesystem>

std::string searchIncludePathsForFile(const string& filename, vector<string> includePaths) {
  for (const auto & includePath : includePaths) {
    string path = includePath + "/" + filename;
    if (std::filesystem::exists(path)) {
      return path;
    }
  }

  return "";
}
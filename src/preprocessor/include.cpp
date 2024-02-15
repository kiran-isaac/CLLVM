#include <args.h>
#include <filesystem>

std::string searchIncludePathsForFile(const string& filename, Args *args) {
  for (const auto & includePath : args->includePaths) {
    string path = includePath + "/" + filename;
    if (std::filesystem::exists(path)) {
      return path;
    }
  }

  return "";
}
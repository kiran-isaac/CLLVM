#include <args.h>

Args::Args(int argc, char** argv) {
  this->includePaths = std::vector<std::string>();

  for (int i = 1; i < argc; i++) {
    if (std::string(argv[i]) == "-o") {
      this->output = argv[i + 1];
      i++;
    } else if (std::string(argv[i]) == "-I") {
      this->includePaths.push_back(argv[i + 1]);
      i++;
    } else if (std::string(argv[i]) == "-L") {
      this->libPath = argv[i + 1];
      i++;
    } else if (std::string(argv[i]) == "-l") {
      this->lib = argv[i + 1];
      i++;
    } else if (std::string(argv[i]) == "-f") {
      this->flags = argv[i + 1];
      i++;
    } else {
      this->source = argv[i];
    }
  }

  for (int i = 0; i < sizeof(defaultLinuxIncludePaths) / sizeof(defaultLinuxIncludePaths[0]); i++) {
    this->includePaths.push_back(defaultLinuxIncludePaths[i]);
  }
}

std::string loadSourceToString(std::string filename) {
  std::ifstream file(filename);
  std::string str;
  std::string file_contents;
  while (std::getline(file, str)) {
    file_contents += str;
    file_contents.push_back('\n');
  }
  return file_contents;
}
#ifndef CLLVM_ARGS_H
#define CLLVM_ARGS_H

#include <string>
#include <fstream>
#include <vector>

using std::string, std::vector;

static string defaultLinuxIncludePaths[] = {"/usr/include", "/usr/local/include"};

class Args {
public:
  std::string source;
  std::string output;
  vector<std::string> includePaths;
  std::string libPath;
  std::string lib;
  std::string flags;
  Args(int argc, char** argv);
  std::string loadSourceToString(std::string source);
};

std::string searchIncludePathsForFile(const string& filename, Args *args);

#endif /* CLLVM_ARGS_H */

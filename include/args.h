#ifndef CLLVM_ARGS_H
#define CLLVM_ARGS_H

#include <string>
#include <fstream>

class Args {
public:
  std::string source;
  std::string output;
  std::string includePath;
  std::string libPath;
  std::string lib;
  std::string flags;
  Args(int argc, char** argv);
  std::string loadSourceToString(std::string source);
};

#endif /* CLLVM_ARGS_H */

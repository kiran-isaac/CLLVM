#include <compile.h>
#include <preprocessor.h>

int compile(const std::string& source) {
  std::string sourceWithoutTrigraphs = removeTrigraphs(source);
  return 0;
}
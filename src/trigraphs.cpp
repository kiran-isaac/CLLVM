#include <preprocessor.h>

std::string removeTrigraphs(const std::string& source) {
  std::string sourceWithoutTrigraphs = source;
  std::string trigraphs[] = {
    "??=", "??/", "??'", "??(", "??)", "??!", "??<", "??>", "??-", "??!"
  };
  std::string replacements[] = {
    "#", "\\", "^", "[", "]", "|", "{", "}", "~", "!"
  };
  for (int i = 0; i < 10; i++) {
    size_t pos = sourceWithoutTrigraphs.find(trigraphs[i]);
    while (pos != std::string::npos) {
      sourceWithoutTrigraphs.replace(pos, 3, replacements[i]);
      pos = sourceWithoutTrigraphs.find(trigraphs[i]);
    }
  }
  return sourceWithoutTrigraphs;
}
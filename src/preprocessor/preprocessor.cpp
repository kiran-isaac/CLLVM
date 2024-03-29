#include <preprocessor/preprocessor.h>

void removeTrigraphs(std::string &source) {
  std::string trigraphs[] = {"??=", "??/", "??'", "??(", "??)",
                             "??!", "??<", "??>", "??-", "??!"};
  std::string replacements[] = {"#", "\\", "^", "[", "]",
                                "|", "{",  "}", "~", "!"};

  for (int i = 0; i < 10; i++) {
    size_t pos = source.find(trigraphs[i]);
    while (pos != std::string::npos) {
      source.replace(pos, 3, replacements[i]);
      pos = source.find(trigraphs[i]);
    }
  }
}

void removeLineSplices(std::string &source) {
  size_t pos = source.find("\\\n");
  while (pos != std::string::npos) {
    source.replace(pos, 2, "");
    pos = source.find("\\\n");
  }
}

void removeComments(std::string &source) {
  size_t pos = source.find("//");
  while (pos != std::string::npos) {
    size_t end = source.find("\n", pos);
    source.replace(pos, end - pos, "");
    pos = source.find("//");
  }

  pos = source.find("/*");
  while (pos != std::string::npos) {
    size_t end = source.find("*/", pos);
    source.replace(pos, end - pos + 2, "");
    pos = source.find("/*");
  }
}

void preprocess(std::string &source) {
  // Translation phase 1: Trigraphs
  removeTrigraphs(source);

  // Translation phase 2: Line splices
  removeLineSplices(source);

  // Translation phase 3: Comments
  removeComments(source);
}

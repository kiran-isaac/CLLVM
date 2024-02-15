#include <preprocessor/preprocessor.h>

std::string removeTrigraphs(const std::string& source) {
  std::string sourceWithoutTrigraphs = source;
  std::string trigraphs[] = {"??=", "??/", "??'", "??(", "??)",
                             "??!", "??<", "??>", "??-", "??!"};
  std::string replacements[] = {"#", "\\", "^", "[", "]",
                                "|", "{",  "}", "~", "!"};
  for (int i = 0; i < 10; i++) {
    size_t pos = sourceWithoutTrigraphs.find(trigraphs[i]);
    while (pos != std::string::npos) {
      sourceWithoutTrigraphs.replace(pos, 3, replacements[i]);
      pos = sourceWithoutTrigraphs.find(trigraphs[i]);
    }
  }
  return sourceWithoutTrigraphs;
}

std::string removeLineSplices(const std::string& source) {
  std::string sourceWithoutLineSplices = source;
  size_t pos = sourceWithoutLineSplices.find("\\\n");
  while (pos != std::string::npos) {
    sourceWithoutLineSplices.replace(pos, 2, "");
    pos = sourceWithoutLineSplices.find("\\\n");
  }
  return sourceWithoutLineSplices;
}

std::string removeComments(const std::string& source) {
  std::string sourceWithoutComments = source;
  size_t pos = sourceWithoutComments.find("//");
  while (pos != std::string::npos) {
    size_t end = sourceWithoutComments.find("\n", pos);
    sourceWithoutComments.replace(pos, end - pos, "");
    pos = sourceWithoutComments.find("//");
  }

  pos = sourceWithoutComments.find("/*");
  while (pos != std::string::npos) {
    size_t end = sourceWithoutComments.find("*/", pos);
    sourceWithoutComments.replace(pos, end - pos + 2, "");
    pos = sourceWithoutComments.find("/*");
  }

  return sourceWithoutComments;
}

std::string preprocess(const std::string& source) {
  // Translation phase 1: Trigraphs
  std::string sourceWithoutTrigraphs = removeTrigraphs(source);

  // Translation phase 2: Line splices
  std::string sourceWithoutLineSplices = removeLineSplices(sourceWithoutTrigraphs);

  // Translation phase 3: Comments, and tokenising into preprocessor tokens
  std::string sourceWithoutComments = removeComments(sourceWithoutLineSplices);
  return sourceWithoutLineSplices;
}


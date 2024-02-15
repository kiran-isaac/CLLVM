#include <args.h>
#include <compile.h>
#include <preprocessor/preprocessor.h>

int compile(Args *args) {
  for (int i = 0; i < args->source.length(); i++) {
    string source = args->loadSourceToString(args->source);

    pre_tokenization_processing(source);
  }
}
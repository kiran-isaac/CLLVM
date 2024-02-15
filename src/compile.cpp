#include <args.h>
#include <compile.h>

int compile(Args *args) {
  for (int i = 0; i < args->source.length(); i++) {
    string source = args->loadSourceToString(args->source);

    preprocess(source)
  }
}
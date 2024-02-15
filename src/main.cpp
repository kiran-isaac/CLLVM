#include <stdio.h>
#include <args.h>
#include <compile.h>

int main(int argc, char** argv) {
  Args *args = new Args(argc, argv);

  for (int i = 0; i < args->source.length(); i++) {
    string source = args->loadSourceToString(args->source);

    compile(source, args);
  }
}
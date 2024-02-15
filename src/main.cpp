#include <stdio.h>
#include <args.h>
#include <compile.h>

int main(int argc, char** argv) {
  Args *args = new Args(argc, argv);
  compile(args);
  delete args;
}
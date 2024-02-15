#ifndef CLLVM_COMPILE_H
#define CLLVM_COMPILE_H

#include <args.h>
#include <preprocessor/preprocessor.h>
#include <string>

using std::string;

int compile(string source, Args *args);

#endif /* CLLVM_COMPILE_H */

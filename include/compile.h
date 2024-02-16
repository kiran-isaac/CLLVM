#ifndef CLLVM_COMPILE_H
#define CLLVM_COMPILE_H

#include <args.h>
#include <string>
#include <lexer.h>

using std::string;

int compile(string source, Args *args);

#endif /* CLLVM_COMPILE_H */

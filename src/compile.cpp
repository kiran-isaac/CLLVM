#include <args.h>
#include <compile.h>
#include <preprocessor/preprocessor.h>

int compile(string source, Args *args) {
  pre_tokenization_processing(source);

  Lexer lexer = Lexer(source);


}
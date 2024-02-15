#include <preprocessor/definitions.h>
#include <time.h>

static string immutableDefinitions[] = {
    "__STDC_MB_MIGHT_NEQ_WC__", "__STDC_VERSION__", "__STDC_HOSTED__",
    "__STDC__", "__DATE__", "__TIME__"};

DefinitionsTable::DefinitionsTable() {
  this->definitions = map<string, string>();

  // Add predefined macros
  this->definitions.insert(
      pair<string, string>("_ _STDC_MB_MIGHT_NEQ_WC_ _ T", "1"));
  this->definitions.insert(pair<string, string>("__STDC_VERSION__", "199901L"));
  this->definitions.insert(pair<string, string>("__STDC_HOSTED__", "1"));
  this->definitions.insert(pair<string, string>("__STDC__", "1"));

  // Add predefined macros for the current date and time
  time_t now = time(0);
  struct tm time_struct;
  char buf[80];
  time_struct = *localtime(&now);
  strftime(buf, sizeof(buf), "%Y%m%d", &time_struct);
  strftime(buf, sizeof(buf), "%H%M%S", &time_struct);
  this->definitions.insert(pair<string, string>("__DATE__", buf));
  this->definitions.insert(pair<string, string>("__TIME__", buf));
};

DefinitionsTable::~DefinitionsTable() { this->definitions.clear(); };

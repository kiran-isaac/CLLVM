#ifndef CLLVM_PREPROCESSOR_DEFINITIONS_H
#define CLLVM_PREPROCESSOR_DEFINITIONS_H

#include <string>
#include <map>
#include <utility>

using std::string, std::map, std::pair;

class DefinitionsTable {
  public:
    DefinitionsTable();
    ~DefinitionsTable();
    void addDefinition(const std::string& name, const std::string& value);
    void removeDefinition(const std::string& name);
    std::string getDefinition(const std::string& name);
  private:
    std::map<std::string, std::string> definitions;
};

#endif /* CLLVM_PREPROCESSOR_DEFINITIONS_H */

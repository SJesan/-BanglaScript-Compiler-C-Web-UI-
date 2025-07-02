#pragma once
#include <string>
#include <unordered_map>
#include "parser.h"

struct Symbol {
    std::string value;
    int line;
};

class SymbolTable {
public:
    void build(const AST& ast);
    void print() const;
    bool exists(const std::string& name) const;
    const Symbol* get(const std::string& name) const;
private:
    std::unordered_map<std::string, Symbol> table;
};

// Run symbol table phase (build and print)
void runSymbolTable(); 
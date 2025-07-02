#include "symbol_table.h"
#include <iostream>

void SymbolTable::build(const AST& ast) {
    table.clear();
    for (const auto& node : ast) {
        if (node.type == ASTNodeType::VarDecl) {
            table[node.varName] = Symbol{node.value, node.line};
        } else if (node.type == ASTNodeType::Assignment) {
            if (table.count(node.varName)) {
                table[node.varName].value = node.value;
            }
        }
    }
}

void SymbolTable::print() const {
    std::cout << "\n[Symbol Table]\n";
    std::cout << "Name\tValue\tLine\n";
    for (const auto& [name, sym] : table) {
        std::cout << name << "\t" << sym.value << "\t" << sym.line << "\n";
    }
}

bool SymbolTable::exists(const std::string& name) const {
    return table.count(name) > 0;
}

const Symbol* SymbolTable::get(const std::string& name) const {
    auto it = table.find(name);
    if (it != table.end()) return &it->second;
    return nullptr;
}

void runSymbolTable() {
    std::cout << "Enter BanglaScript code for symbol table (end with # on a new line):\n";
    std::string input, line;
    while (std::getline(std::cin, line) && line != "#")
        input += line + "\n";
    TokenList tokens = tokenize(input);
    AST ast = parseTokens(tokens);
    SymbolTable symtab;
    symtab.build(ast);
    symtab.print();
} 
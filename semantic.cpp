#include "semantic.h"
#include <iostream>
#include <unordered_set>

void semanticCheck(const AST& ast, const SymbolTable& symtab) {
    bool error = false;
    std::unordered_set<std::string> declared;
    for (const auto& node : ast) {
        if (node.type == ASTNodeType::VarDecl) {
            if (declared.count(node.varName)) {
                std::cerr << "[Semantic] Error: Duplicate declaration of '" << node.varName << "' at line " << node.line << "\n";
                error = true;
            } else {
                declared.insert(node.varName);
            }
        } else if (node.type == ASTNodeType::Assignment || node.type == ASTNodeType::PrintStmt) {
            if (!declared.count(node.varName)) {
                std::cerr << "[Semantic] Error: Undeclared variable '" << node.varName << "' at line " << node.line << "\n";
                error = true;
            }
        }
    }
    if (!error) std::cout << "[Semantic] No semantic errors found.\n";
}

void runSemanticAnalyzer() {
    std::cout << "Enter BanglaScript code for semantic analysis (end with # on a new line):\n";
    std::string input, line;
    while (std::getline(std::cin, line) && line != "#")
        input += line + "\n";
    TokenList tokens = tokenize(input);
    AST ast = parseTokens(tokens);
    SymbolTable symtab;
    symtab.build(ast);
    symtab.print();
    semanticCheck(ast, symtab);
} 
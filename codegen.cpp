#include "codegen.h"
#include <iostream>

void generateCode(const AST& ast) {
    std::cout << "\n[BanglaScript Pseudo Code]" << std::endl;
    for (const auto& node : ast) {
        if (node.type == ASTNodeType::VarDecl) {
            if (!node.value.empty()) {
                std::cout << node.varName << " = " << node.value << ";" << std::endl;
            } else {
                std::cout << node.varName << ";" << std::endl;
            }
        } else if (node.type == ASTNodeType::Assignment) {
            std::cout << node.varName << " = " << node.value << ";" << std::endl;
        } else if (node.type == ASTNodeType::PrintStmt) {
            std::cout << "print(" << node.varName << ");" << std::endl;
        }
    }
}

void runCodeGen() {
    std::cout << "Enter BanglaScript code for code generation (end with # on a new line):\n";
    std::string input, line;
    while (std::getline(std::cin, line) && line != "#")
        input += line + "\n";
    TokenList tokens = tokenize(input);
    AST ast = parseTokens(tokens);
    generateCode(ast);
} 
#include <iostream>
#include <iomanip>
#include "lexer.h"
#include "parser.h"
#include "semantic.h"
#include "symbol_table.h"
#include "codegen.h"

int main() {
    std::cout << "\n🔍 Lexical Analysis (Tokens)\n";
    std::cout << std::string(27, '-') << "\n";
    std::string input, line;
    std::cout << "Enter your BanglaScript code (end with # on a new line):\n";
    while (std::getline(std::cin, line) && line != "#")
        input += line + "\n";
    TokenList tokens = tokenize(input);
    for (const auto& token : tokens) {
        std::string typeStr;
        switch (token.type) {
            case TokenType::Keyword: typeStr = "Keyword"; break;
            case TokenType::Identifier: typeStr = "Identifier"; break;
            case TokenType::Number: typeStr = "Number"; break;
            case TokenType::Operator: typeStr = "Operator"; break;
            case TokenType::Separator: typeStr = "Separator"; break;
            case TokenType::StringLiteral: typeStr = "StringLiteral"; break;
            case TokenType::Comment: typeStr = "Comment"; break;
            case TokenType::EndOfFile: typeStr = "EOF"; break;
            default: typeStr = "Unknown";
        }
        std::cout << "[" << typeStr << "] '" << token.value << "' (Line: " << token.line << ", Col: " << token.column << ")\n";
    }

    std::cout << "\n🌳 Syntax Analysis (AST)\n";
    std::cout << std::string(24, '-') << "\n";
    AST ast = parseTokens(tokens);
    for (const auto& node : ast) {
        if (node.type == ASTNodeType::VarDecl) {
            std::cout << "[VarDecl] Name: " << node.varName;
            if (!node.value.empty()) std::cout << ", Init: " << node.value;
            std::cout << " (Line: " << node.line << ")\n";
        } else if (node.type == ASTNodeType::Assignment) {
            std::cout << "[Assign] Name: " << node.varName << " = " << node.value << " (Line: " << node.line << ")\n";
        } else if (node.type == ASTNodeType::PrintStmt) {
            std::cout << "[Print] dekhao(" << node.varName << ") (Line: " << node.line << ")\n";
        }
    }

    std::cout << "\n📦 Symbol Table\n";
    std::cout << std::string(15, '-') << "\n";
    SymbolTable symtab;
    symtab.build(ast);
    std::cout << "| Name  | Value | Line |\n";
    std::cout << "|-------|-------|------|\n";
    for (const auto& [name, sym] : symtab.table) {
        std::cout << "| " << std::setw(5) << std::left << name << " | " << std::setw(5) << sym.value << " | " << std::setw(4) << sym.line << " |\n";
    }
    if (symtab.table.empty()) {
        std::cout << "(No variables declared)\n";
    }

    std::cout << "\n🛡️ Semantic Analysis\n";
    std::cout << std::string(20, '-') << "\n";
    bool error = false;
    std::unordered_set<std::string> declared;
    for (const auto& node : ast) {
        if (node.type == ASTNodeType::VarDecl) {
            if (declared.count(node.varName)) {
                std::cout << "❌ [Semantic Error] Duplicate declaration of '" << node.varName << "' at line " << node.line << "\n";
                error = true;
            } else {
                declared.insert(node.varName);
            }
        } else if (node.type == ASTNodeType::Assignment || node.type == ASTNodeType::PrintStmt) {
            if (!declared.count(node.varName)) {
                std::cout << "❌ [Semantic Error] Undeclared variable '" << node.varName << "' at line " << node.line << "\n";
                error = true;
            }
        }
    }
    if (!error) std::cout << "✅ No semantic errors found.\n";

    std::cout << "\n📝 Code Generation (BanglaScript Pseudo Code)\n";
    std::cout << std::string(44, '-') << "\n";
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
    return 0;
} 
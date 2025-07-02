#pragma once
#include <vector>
#include <string>
#include "lexer.h"

// AST Node Types for BanglaScript
enum class ASTNodeType {
    VarDecl,   // dhori x = 10;
    Assignment, // x = 5;
    PrintStmt   // dekhao(x);
};

struct ASTNode {
    ASTNodeType type;
    std::string varName;   // For VarDecl, Assignment, PrintStmt
    std::string value;     // For Assignment, VarDecl (init value)
    int line;
};

using AST = std::vector<ASTNode>;

// Parse tokens into AST (BanglaScript)
AST parseTokens(const TokenList& tokens);

// Run parser (calls lexer, parses, and prints AST)
void runParser(); 
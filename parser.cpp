#include "parser.h"
#include <iostream>

// Helper: check if a token is a type keyword
static bool isTypeKeyword(const Token& token) {
    return token.type == TokenType::Keyword &&
        (token.value == "int" || token.value == "float" || token.value == "char" || token.value == "double");
}

// Parse tokens into AST for BanglaScript
AST parseTokens(const TokenList& tokens) {
    AST ast;
    size_t i = 0;
    while (i < tokens.size()) {
        // Variable declaration: dhori id [= value] ;
        if (tokens[i].type == TokenType::Keyword && tokens[i].value == "dhori" &&
            i + 1 < tokens.size() && tokens[i+1].type == TokenType::Identifier) {
            ASTNode node;
            node.type = ASTNodeType::VarDecl;
            node.varName = tokens[i+1].value;
            node.line = tokens[i].line;
            i += 2;
            // Optional initialization
            if (i < tokens.size() && tokens[i].type == TokenType::Operator && tokens[i].value == "=") {
                ++i;
                if (i < tokens.size() && (tokens[i].type == TokenType::Number || tokens[i].type == TokenType::Identifier)) {
                    node.value = tokens[i].value;
                    ++i;
                }
            }
            // Expect semicolon
            if (i < tokens.size() && tokens[i].type == TokenType::Separator && tokens[i].value == ";") {
                ++i;
                ast.push_back(node);
                continue;
            } else {
                std::cerr << "[Parser] Error: Expected ';' after declaration at line " << node.line << "\n";
                break;
            }
        }
        // Print statement: dekhao ( id ) ;
        if (tokens[i].type == TokenType::Keyword && tokens[i].value == "dekhao" &&
            i + 3 < tokens.size() && tokens[i+1].type == TokenType::Separator && tokens[i+1].value == "(" &&
            tokens[i+2].type == TokenType::Identifier &&
            tokens[i+3].type == TokenType::Separator && tokens[i+3].value == ")") {
            ASTNode node;
            node.type = ASTNodeType::PrintStmt;
            node.varName = tokens[i+2].value;
            node.line = tokens[i].line;
            i += 4;
            // Expect semicolon
            if (i < tokens.size() && tokens[i].type == TokenType::Separator && tokens[i].value == ";") {
                ++i;
                ast.push_back(node);
                continue;
            } else {
                std::cerr << "[Parser] Error: Expected ';' after print statement at line " << node.line << "\n";
                break;
            }
        }
        // Assignment: id = value ;
        if (tokens[i].type == TokenType::Identifier &&
            i + 2 < tokens.size() && tokens[i+1].type == TokenType::Operator && tokens[i+1].value == "=" &&
            (tokens[i+2].type == TokenType::Number || tokens[i+2].type == TokenType::Identifier)) {
            ASTNode node;
            node.type = ASTNodeType::Assignment;
            node.varName = tokens[i].value;
            node.value = tokens[i+2].value;
            node.line = tokens[i].line;
            i += 3;
            // Expect semicolon
            if (i < tokens.size() && tokens[i].type == TokenType::Separator && tokens[i].value == ";") {
                ++i;
                ast.push_back(node);
                continue;
            } else {
                std::cerr << "[Parser] Error: Expected ';' after assignment at line " << node.line << "\n";
                break;
            }
        }
        // Skip to next token if not matched
        ++i;
    }
    return ast;
}

// Run parser: get input, tokenize, parse, print AST
void runParser() {
    std::cout << "Enter BanglaScript code to parse (end with # on a new line):\n";
    std::string input, line;
    while (std::getline(std::cin, line) && line != "#")
        input += line + "\n";
    TokenList tokens = tokenize(input);
    AST ast = parseTokens(tokens);
    std::cout << "\n[Parser] AST Nodes:\n";
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
} 
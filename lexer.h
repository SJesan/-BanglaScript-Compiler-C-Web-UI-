#pragma once
#include <string>
#include <vector>

// Token types
enum class TokenType {
    Keyword,
    Identifier,
    Number,
    Operator,
    Separator,
    StringLiteral,
    Comment,
    EndOfFile,
    Unknown
};

struct Token {
    TokenType type;
    std::string value;
    int line;
    int column;
};

// List of tokens
using TokenList = std::vector<Token>;

// Main lexer function
TokenList tokenize(const std::string& input);

// Run lexer and print tokens
void runLexer(const std::string& input); 
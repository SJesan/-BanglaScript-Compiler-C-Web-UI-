#include "lexer.h"
#include <iostream>
#include <cctype>
#include <unordered_set>

// List of BanglaScript keywords
static const std::unordered_set<std::string> keywords = {
    "dhori", "dekhao", "jodi", "othoba", "jotokkhon", "function", "ferot"
};

// List of single-character operators and separators
static const std::unordered_set<char> operators = {'+', '-', '*', '/', '=', '<', '>', '!', '&', '|', '%'};
static const std::unordered_set<char> separators = {';', ',', '(', ')', '{', '}', '[', ']'};

// Helper: check if a string is a keyword
static bool isKeyword(const std::string& str) {
    return keywords.count(str) > 0;
}

TokenList tokenize(const std::string& input) {
    TokenList tokens;
    int line = 1, col = 1;
    size_t i = 0, n = input.size();
    while (i < n) {
        char c = input[i];
        // Skip whitespace
        if (c == ' ' || c == '\t' || c == '\r') { ++i; ++col; continue; }
        if (c == '\n') { ++i; ++line; col = 1; continue; }
        // Skip comments
        if (c == '/' && i + 1 < n && (input[i+1] == '/' || input[i+1] == '*')) {
            if (input[i+1] == '/') {
                // Single-line comment
                i += 2; col += 2;
                while (i < n && input[i] != '\n') { ++i; ++col; }
                continue;
            } else {
                // Multi-line comment
                i += 2; col += 2;
                while (i + 1 < n && !(input[i] == '*' && input[i+1] == '/')) {
                    if (input[i] == '\n') { ++line; col = 1; } else { ++col; }
                    ++i;
                }
                if (i + 1 < n) { i += 2; col += 2; } // skip closing */
                continue;
            }
        }
        // Identifiers or keywords
        if (std::isalpha(c) || c == '_') {
            size_t start = i;
            int start_col = col;
            while (i < n && (std::isalnum(input[i]) || input[i] == '_')) { ++i; ++col; }
            std::string word = input.substr(start, i - start);
            tokens.push_back({isKeyword(word) ? TokenType::Keyword : TokenType::Identifier, word, line, start_col});
            continue;
        }
        // Numbers
        if (std::isdigit(c)) {
            size_t start = i;
            int start_col = col;
            while (i < n && std::isdigit(input[i])) { ++i; ++col; }
            tokens.push_back({TokenType::Number, input.substr(start, i - start), line, start_col});
            continue;
        }
        // String literals
        if (c == '"') {
            size_t start = i;
            int start_col = col;
            ++i; ++col;
            while (i < n && input[i] != '"') {
                if (input[i] == '\\' && i + 1 < n) { i += 2; col += 2; }
                else { ++i; ++col; }
            }
            if (i < n) { ++i; ++col; }
            tokens.push_back({TokenType::StringLiteral, input.substr(start, i - start), line, start_col});
            continue;
        }
        // Operators (handle two-character operators)
        if (operators.count(c)) {
            int start_col = col;
            std::string op(1, c);
            if (i + 1 < n && (input[i+1] == '=' || (c == '&' && input[i+1] == '&') || (c == '|' && input[i+1] == '|'))) {
                op += input[i+1];
                ++i; ++col;
            }
            tokens.push_back({TokenType::Operator, op, line, start_col});
            ++i; ++col;
            continue;
        }
        // Separators
        if (separators.count(c)) {
            tokens.push_back({TokenType::Separator, std::string(1, c), line, col});
            ++i; ++col;
            continue;
        }
        // Unknown character
        tokens.push_back({TokenType::Unknown, std::string(1, c), line, col});
        ++i; ++col;
    }
    tokens.push_back({TokenType::EndOfFile, "", line, col});
    return tokens;
}

void runLexer(const std::string& input) {
    TokenList tokens = tokenize(input);
    std::cout << "\n[Lexer] Tokens:\n";
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
} 
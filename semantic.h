#pragma once
#include "parser.h"
#include "symbol_table.h"

// Perform semantic analysis: check for undeclared variables, duplicate declarations, etc.
void semanticCheck(const AST& ast, const SymbolTable& symtab);

// Run semantic analyzer (get input, build AST, symbol table, check semantics)
void runSemanticAnalyzer(); 
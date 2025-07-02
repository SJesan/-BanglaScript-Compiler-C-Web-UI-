#pragma once
#include "parser.h"

// Generate pseudo code from AST for BanglaScript
void generateCode(const AST& ast);

// Run code generation (get input, build AST, generate code)
void runCodeGen(); 
// utils.h
#ifndef UTILS_H
#define UTILS_H

#include "tokenizer.h"
#include "parser.h"
#include "interpreter.h"

void print_tokens(Token* tokens);
void print_ast(Program* program);
char* read_file(const char* filename);

#endif // UTILS_H

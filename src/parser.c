#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

typedef struct ASTNode {
    // Add your AST node structure here
} ASTNode;

ASTNode* parse(Token* tokens);

void free_ast(ASTNode* root);

#endif

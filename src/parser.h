#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"

typedef struct ASTNode {
    char* value;
    struct ASTNode* left;
    struct ASTNode* right;
    struct ASTNode* body;
} ASTNode;

ASTNode* parse(Token* tokens);

#endif // PARSER_H

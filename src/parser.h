#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct ASTNode {
    int type;
    char *value;
    struct ASTNode *left;
    struct ASTNode *right;
    struct ASTNode *body;
} ASTNode;

ASTNode* create_node(int type, char* value);

ASTNode* parse(Token* tokens);

#endif // PARSER_H

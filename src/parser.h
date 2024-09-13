#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"

typedef struct NodeDeclaration {
    char *name;
    int value;
    struct NodeDeclaration **parents; // Array of parent nodes
    int parentCount; // Number of parent nodes
    struct NodeDeclaration *next;
} NodeDeclaration;

typedef struct PrintStatement {
    char *variable;
    struct PrintStatement *next;
} PrintStatement;

typedef struct ForLoop {
    char *variable;
    char *start;
    char *end;
    PrintStatement *printStatements;
    struct ForLoop *next;
} ForLoop;

typedef struct ParentNode {
    char *name;
    struct ParentNode *next;
} ParentNode;

typedef struct Program {
    NodeDeclaration *nodeDeclarations;
    ForLoop *forLoops;
    ParentNode *parentNodes;
} Program;

typedef struct Parser {
    Token *tokens;
    int current;
    int tokenCount;
    NodeDeclaration *nodeDeclarations;
} Parser;

typedef struct ASTNode {
    int data;
    struct Node* next;
} ASTNode;

Program* parse(Token* tokens);
int countTokens(Token *tokens);


#endif // PARSER_H

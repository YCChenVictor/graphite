#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"

typedef struct EdgeDeclaration {
    char *name;
    char *from;
    char *to;
    struct EdgeDeclaration *next;
} EdgeDeclaration;

typedef struct NodeDeclaration {
    char *name;
    char *parent;
    int value;
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

typedef struct Program {
    NodeDeclaration *nodeDeclarations;
    EdgeDeclaration *edgeDeclarations; // Add this line
    ForLoop *forLoops;
} Program;

typedef struct Parser {
    Token *tokens;
    int current;
    int tokenCount;
} Parser;

typedef struct ASTNode {
    int data;
    struct Node* next;
} ASTNode;

Program* parse(Token* tokens);
int countTokens(Token *tokens);


#endif // PARSER_H

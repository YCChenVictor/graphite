#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stdlib.h>
#include <string.h>
#include "parser.h"

typedef struct GraphNode {
    char* value;
    struct GraphNode** children;
    int child_count;
} GraphNode;

GraphNode* astToGraph(ASTNode* ast);
void executeGraph(GraphNode* graph);
void interpret(ASTNode* ast);

#endif // INTERPRETER_H

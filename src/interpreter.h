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

void executeGraph(GraphNode* graph);

#endif // INTERPRETER_H

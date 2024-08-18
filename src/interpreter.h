#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stdlib.h>
#include <string.h>
#include "parser.h"

typedef struct AdjListNode {
    int dest;
    char* name;
    struct AdjListNode* next;
} AdjListNode;

typedef struct AdjList {
    AdjListNode* head;
} AdjList;

typedef struct Graph {
    int num_vertices;
    AdjList* array;
} Graph;

void interpret(Program* node);

#endif // INTERPRETER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpreter.h"

GraphNode* astToGraph(ASTNode* ast) {
    // Simplified AST to graph conversion logic
    GraphNode* graph = malloc(sizeof(GraphNode));
    graph->value = strdup(ast->value);
    graph->child_count = 1;
    graph->children = malloc(sizeof(GraphNode*) * graph->child_count);
    graph->children[0] = malloc(sizeof(GraphNode));
    graph->children[0]->value = strdup(ast->body->value);
    graph->children[0]->child_count = 0;
    graph->children[0]->children = NULL;

    return graph;
}

void executeGraph(GraphNode* graph) {
    // Simplified graph traversal and execution logic
    if (strcmp(graph->value, "for") == 0) {
        int start = 0;
        int end = 10;
        for (int i = start; i < end; i++) {
            if (strcmp(graph->children[0]->value, "print") == 0) {
                printf("%d\n", i);
            }
        }
    }
}

void interpret(ASTNode* ast) {
    GraphNode* graph = astToGraph(ast);
    executeGraph(graph);
    // freeGraph(graph);
}

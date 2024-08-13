#include <stdio.h>
#include "interpreter.h"

GraphNode* astToGraph(ASTNode* ast) {
    // Simplified AST to graph conversion logic
    GraphNode* graph = malloc(sizeof(GraphNode));
    graph->value = strdup(ast->value);
    graph->child_count = 1;
    graph->children = malloc(sizeof(GraphNode*) * graph->child_count);
    graph->children[0] = malloc(sizeof(GraphNode));
    graph->children[0]->value = strdup(ast->left->value);
    graph->children[0]->child_count = 0;
    graph->children[0]->children = NULL;

    return graph;
}

void executeGraph(GraphNode* graph) {
    // Simplified graph traversal and execution logic
    if (strcmp(graph->value, "print") == 0) {
        printf("%s\n", graph->children[0]->value);
    }
}

void interpret(ASTNode* ast) {
    GraphNode* graph = astToGraph(ast);
    executeGraph(graph);
    // freeGraph(graph);
}

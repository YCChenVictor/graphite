#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "interpreter.h"

// use not use dfs to build up the path, so seems we do not need the ForLoop 
void dfs(NodeDeclaration* node, NodeDeclaration* nodes[], int* visited, int size) {
    if (!node || visited[node->value]) return;
    printf("%d\n", node->value);
    visited[node->value] = 1;

    for (int i = 0; i < size; i++) {
        if (nodes[i] && strcmp(nodes[i]->parent, node->name) == 0) {
            dfs(nodes[i], nodes, visited, size);
        }
    }
}

void interpret(Program* program) {
    NodeDeclaration* nodeDecl = program->nodeDeclarations;
    int size = 0;
    while (nodeDecl) {
        size++;
        nodeDecl = nodeDecl->next;
    }

    NodeDeclaration* nodes[size];
    int visited[size];
    for (int i = 0; i < size; i++) visited[i] = 0;

    nodeDecl = program->nodeDeclarations;
    for (int i = 0; i < size; i++) {
        nodes[i] = nodeDecl;
        nodeDecl = nodeDecl->next;
    }

    nodeDecl = program->nodeDeclarations;
    while (nodeDecl) {
        if (strcmp(nodeDecl->parent, "null") == 0) {
            dfs(nodeDecl, nodes, visited, size);
        }
        nodeDecl = nodeDecl->next;
    }

    // ForLoop* forLoop = program->forLoops;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "interpreter.h"

int count_nodes(NodeDeclaration* head) {
    int count = 0;
    NodeDeclaration* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

Graph* create_graph(int num_vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (graph == NULL) {
        fprintf(stderr, "Failed to allocate memory for graph\n");
        exit(EXIT_FAILURE);
    }
    graph->num_vertices = num_vertices;
    graph->array = (AdjList*)malloc(num_vertices * sizeof(AdjList));
    if (graph->array == NULL) {
        fprintf(stderr, "Failed to allocate memory for graph array\n");
        free(graph);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < num_vertices; ++i) {
        graph->array[i].head = NULL;
    }
    return graph;
}

AdjListNode* new_adj_list_node(int dest) {
    AdjListNode* new_node = (AdjListNode*)malloc(sizeof(AdjListNode));
    new_node->dest = dest;
    new_node->next = NULL;
    return new_node;
}

void add_edge(Graph* graph, int src, int dest, const char* name) {
    AdjListNode* newNode = new_adj_list_node(dest);
    newNode->name = strdup(name); // Allocate memory and copy the name

    if (graph->array[src].head == NULL || graph->array[src].head->dest > dest) {
        newNode->next = graph->array[src].head;
        graph->array[src].head = newNode;
    } else {
        AdjListNode* current = graph->array[src].head;
        while (current->next != NULL && current->next->dest < dest) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

void dfsUtil(Graph* graph, int v, int endNode, int* visited, bool* endReached) {
    if (*endReached) return; // Stop if end node has been reached

    visited[v] = 1;
    printf("%d ", v);

    if (v == endNode) {
        *endReached = true;
        return;
    }

    AdjListNode* pCrawl = graph->array[v].head;
    while (pCrawl != NULL) {
        if (!visited[pCrawl->dest]) {
            dfsUtil(graph, pCrawl->dest, endNode, visited, endReached);
        }
        pCrawl = pCrawl->next;
    }
}


void dfs(Graph* graph, int startVertex, int endNode) {
    // Mark all the vertices as not visited
    int* visited = (int*)malloc(graph->num_vertices * sizeof(int));
    for (int i = 0; i < graph->num_vertices; i++) {
        visited[i] = 0;
    }

    bool endReached = false; // Initialize the flag

    // Call the recursive helper function to print DFS traversal
    dfsUtil(graph, startVertex, endNode, visited, &endReached);

    free(visited);
}

void print_graph(Graph* graph) {
    for (int v = 0; v < graph->num_vertices; ++v) {
        AdjListNode* pCrawl = graph->array[v].head;
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (pCrawl) {
            printf("-> %d", pCrawl->dest);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

void interpret(Program* program) {
    NodeDeclaration* nodeDecl = program->nodeDeclarations;
    ForLoop* forLoop = program->forLoops;
    Graph* graph = create_graph(count_nodes(nodeDecl));

    // Add edges to the graph
    while (nodeDecl != NULL) {
        if (nodeDecl->parent != NULL) {
            NodeDeclaration* parentDecl = program->nodeDeclarations;
            while (parentDecl != NULL) {
                if (strcmp(parentDecl->name, nodeDecl->parent) == 0) {
                    add_edge(graph, parentDecl->value, nodeDecl->value, nodeDecl->name);
                    break;
                }
                parentDecl = parentDecl->next;
            }
        }
        nodeDecl = nodeDecl->next;
    }

    // Find start and end nodes by name
    int startNode = -1, endNode = -1;
    nodeDecl = program->nodeDeclarations;
    while (nodeDecl != NULL) {
        if (strcmp(nodeDecl->name, forLoop->start) == 0) {
            startNode = nodeDecl->value;
        }
        if (strcmp(nodeDecl->name, forLoop->end) == 0) {
            endNode = nodeDecl->value;
        }
        nodeDecl = nodeDecl->next;
    }

    if (startNode == -1 || endNode == -1) {
        printf("Start or end node not found\n");
        return;
    }

    dfs(graph, startNode, endNode);
}


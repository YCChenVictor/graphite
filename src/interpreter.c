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

void dfs_util(Graph* graph, int currentVertex, int endNode, int* visited, bool* endReached, int* path, int pathIndex, int* finalPath, int* finalPathLength, int* shortestPathLength) {
    visited[currentVertex] = 1;
    path[pathIndex] = currentVertex;
    pathIndex++;

    if (currentVertex == endNode) {
        *endReached = true;
        if (pathIndex < *shortestPathLength) {
            *shortestPathLength = pathIndex;
            *finalPathLength = pathIndex;
            for (int i = 0; i < pathIndex; i++) {
                finalPath[i] = path[i];
            }
        }
    } else {
        AdjListNode* adjList = graph->array[currentVertex].head;
        while (adjList != NULL) {
            int connectedVertex = adjList->dest;
            if (!visited[connectedVertex]) {
                dfs_util(graph, connectedVertex, endNode, visited, endReached, path, pathIndex, finalPath, finalPathLength, shortestPathLength);
            }
            adjList = adjList->next;
        }
    }

    pathIndex--;
    visited[currentVertex] = 0;
}

void dfs(Graph* graph, int startVertex, int endNode) {
    int* visited = (int*)malloc(graph->num_vertices * sizeof(int));
    for (int i = 0; i < graph->num_vertices; i++) {
        visited[i] = 0;
    }

    bool endReached = false;
    int path[graph->num_vertices];
    int finalPath[graph->num_vertices];
    int finalPathLength = 0;
    int shortestPathLength = graph->num_vertices + 1; // Initialize with a large value

    dfs_util(graph, startVertex, endNode, visited, &endReached, path, 0, finalPath, &finalPathLength, &shortestPathLength);

    // Print the final path
    for (int i = 0; i < finalPathLength; i++) {
        printf("%d ", finalPath[i]);
    }
    // printf("\n");

    // Print the final path length
    // printf("Final Path Length: %d\n", finalPathLength);

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
    EdgeDeclaration* edgeDecl = program->edgeDeclarations;
    NodeDeclaration* nodeDecl = program->nodeDeclarations;
    ForLoop* forLoop = program->forLoops;
    Graph* graph = create_graph(count_nodes(nodeDecl));

    // Add edges to the graph
    while (edgeDecl != NULL) {
        NodeDeclaration* fromNode = NULL;
        NodeDeclaration* toNode = NULL;

        // Find the 'from' node
        if (edgeDecl->from != NULL) {
            NodeDeclaration* nodeDecl = program->nodeDeclarations;
            while (nodeDecl != NULL) {
                if (strcmp(nodeDecl->name, edgeDecl->from) == 0) {
                    fromNode = nodeDecl;
                    break;
                }
                nodeDecl = nodeDecl->next;
            }
        }

        // Find the 'to' node
        NodeDeclaration* nodeDecl = program->nodeDeclarations;
        while (nodeDecl != NULL) {
            if (strcmp(nodeDecl->name, edgeDecl->to) == 0) {
                toNode = nodeDecl;
                break;
            }
            nodeDecl = nodeDecl->next;
        }

        // Add the edge if both nodes are found
        if (toNode != NULL && (fromNode != NULL || edgeDecl->from == NULL)) {
            add_edge(graph, fromNode ? fromNode->value : -1, toNode->value, edgeDecl->name);
        }

        edgeDecl = edgeDecl->next;
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


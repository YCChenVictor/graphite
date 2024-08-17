// utils.c
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void print_tokens(Token* tokens) {
    // Assuming tokens is an array terminated by a special token or NULL
    for (int i = 0; tokens[i].value != NULL; i++) {
        printf("Token: %s\n", tokens[i].value);
    }
}

void print_ast(Program* program) {
    NodeDeclaration* nodeDecl = program->nodeDeclarations;
    while (nodeDecl) {
        printf("NodeDeclaration: %s, Parent: %s, Value: %d\n", nodeDecl->name, nodeDecl->parent, nodeDecl->value);
        nodeDecl = nodeDecl->next;
    }

    ForLoop* forLoop = program->forLoops;
    while (forLoop) {
        printf("ForLoop: Variable: %s, Start: %s, End: %s\n", forLoop->variable, forLoop->start, forLoop->end);
        PrintStatement* printStmt = forLoop->printStatements;
        while (printStmt) {
            printf("    PrintStatement: Variable: %s\n", printStmt->variable);
            printStmt = printStmt->next;
        }
        forLoop = forLoop->next;
    }
}

char* read_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file");
        return NULL;
    }

    // Get the file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate buffer to hold the file contents
    char* input = (char*)malloc(file_size + 1);
    if (input == NULL) {
        perror("Failed to allocate memory");
        fclose(file);
        return NULL;
    }

    // Read the file into the buffer
    fread(input, 1, file_size, file);
    input[file_size] = '\0'; // Null-terminate the string

    fclose(file);
    return input;
}

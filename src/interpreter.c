#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpreter.h"

#define FOR_LOOP 1
#define LOOP_VARIABLE 2
#define ITERABLE 3
#define FUNCTION_CALL 4
#define ARGUMENT 5

void interpret(ASTNode* node) {
    if (node == NULL) {
        return;
    }

    printf("Node Type: %d, Value: %s\n", node->type, node->value ? node->value : "(null)");

    switch (node->type) {
        case FOR_LOOP:
            printf("Executing for loop with variable %s\n", node->left->value);
            interpret(node->body);
            break;

        case FUNCTION_CALL:
            printf("Function call: %s\n", node->value);
            interpret(node->left); // Interpret the argument
            break;

        case ARGUMENT:
            printf("Argument: %s\n", node->value);
            break;

        default:
            printf("Unknown node type: %d\n", node->type);
            break;
    }

    interpret(node->left);
    interpret(node->right);
    interpret(node->body);
}

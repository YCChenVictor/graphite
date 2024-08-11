#include <stdio.h>
#include "interpreter.h"
#include "parser.h"

// Function to interpret the AST
void interpret(ASTNode* root) {
    if (root == NULL) {
        return; // Base case: if the node is null, do nothing
    }

    switch (root->type) {
        case NODE_LITERAL: // Assuming NODE_LITERAL is defined in parser.h
            // For a literal node, print its value
            printf("Literal: %d\n", root->value); // Adjust this based on your value type
            break;

        case NODE_VARIABLE: // Assuming NODE_VARIABLE is defined in parser.h
            // Handle variable nodes (e.g., lookup variable value)
            printf("Variable: %s\n", root->identifier); // Assuming identifier is a string
            break;

        case NODE_ASSIGNMENT: // Assuming NODE_ASSIGNMENT is defined in parser.h
            // Handle assignments (e.g., set variable values)
            printf("Assignment: %s = ", root->left->identifier);
            interpret(root->right); // Interpret the right-hand side
            break;

        case NODE_BINARY_OP: // Assuming NODE_BINARY_OP is defined in parser.h
            // Handle binary operations (e.g., addition, subtraction)
            interpret(root->left); // Interpret the left operand
            printf("Operator: %s\n", root->operator); // Assuming operator is a string
            interpret(root->right); // Interpret the right operand
            break;

        // Add more cases as needed based on your AST structure

        default:
            printf("Unknown AST Node Type: %d\n", root->type);
            break;
    }
}

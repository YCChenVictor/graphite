#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

// Function to create a new AST node
ASTNode* create_ast_node(int type) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = type;
    return node;
}

// Function to parse tokens and create an AST
ASTNode* parse(Token* tokens) {
    // Simple parsing logic: for demonstration, we will only handle a single expression
    Token* current_token = tokens;

    if (current_token->type == TOKEN_IDENTIFIER) {
        // If the token is an identifier, create a variable node
        ASTNode* variable_node = create_ast_node(NODE_VARIABLE);
        variable_node->identifier = strdup(current_token->value);
        current_token++; // Move to the next token

        // Check for assignment
        if (current_token->type == TOKEN_OPERATOR && current_token->value[0] == '=') {
            ASTNode* assignment_node = create_ast_node(NODE_ASSIGNMENT);
            assignment_node->left = variable_node;
            current_token++; // Move past '='

            // Expect a literal or another variable as the right-hand side
            if (current_token->type == TOKEN_NUMBER) {
                ASTNode* literal_node = create_ast_node(NODE_LITERAL);
                literal_node->value = atoi(current_token->value);
                assignment_node->right = literal_node;
                return assignment_node; // Return the assignment node
            }
        }
    }

    // If no valid node was created, return NULL (or handle invalid case)
    return NULL;
}

// Function to free the AST
void free_ast(ASTNode* root) {
    if (root == NULL) {
        return;
    }

    // Recursively free children based on node type
    switch (root->type) {
        case NODE_VARIABLE:
            free(root->identifier); // Free the identifier string
            break;
        case NODE_ASSIGNMENT:
            free_ast(root->left); // Free left child
            free_ast(root->right); // Free right child
            break;
        case NODE_LITERAL:
            // No additional resources to free for literals
            break;
        // Handle additional node types as needed
        default:
            break;
    }

    free(root); // Free the AST node itself
}

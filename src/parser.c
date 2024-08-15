#include "parser.h"
#include <stdlib.h>

#define FOR_LOOP 1
#define LOOP_VARIABLE 2
#define ITERABLE 3
#define FUNCTION_CALL 4
#define ARGUMENT 5

ASTNode* create_node(int type, char* value) {
    // Allocate memory for the new node
    ASTNode* new_node = (ASTNode*)malloc(sizeof(ASTNode));
    if (new_node == NULL) {
        // Handle memory allocation failure
        return NULL;
    }

    // Initialize the node's type and value
    new_node->type = type;
    new_node->value = value ? strdup(value) : NULL; // Duplicate the string to avoid issues with token memory
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->body = NULL;

    // Return the pointer to the new node
    return new_node;
}

ASTNode* parse(Token* tokens) {
    int index = 0;

    // Create the root node for the 'for' loop
    ASTNode* root = create_node(FOR_LOOP, tokens[index++].value); // 'for'

    // Create the node for the loop variable
    ASTNode* var_node = create_node(LOOP_VARIABLE, tokens[index++].value); // 'node'
    root->left = var_node;

    // Skip the 'in' token
    index++;

    // Create the node for the iterable
    ASTNode* iterable_node = create_node(ITERABLE, tokens[index++].value); // 'graph'
    root->right = iterable_node;

    // Create the body node
    ASTNode* body_node = create_node(FUNCTION_CALL, tokens[index++].value); // 'doSomething'
    root->body = body_node;

    // Create the argument node for the function call
    ASTNode* arg_node = create_node(ARGUMENT, tokens[index++].value); // 'node'
    body_node->left = arg_node;

    return root;
}

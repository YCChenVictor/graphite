#include "parser.h"
#include <stdlib.h>

ASTNode* create_node(int type, char* value) {
    // Allocate memory for the new node
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        // Handle memory allocation failure
        return NULL;
    }

    // Initialize the node's data and next pointer
    new_node->data = atoi(value);
    new_node->next = NULL;

    // Return the pointer to the new node
    return (ASTNode *)new_node;
}

ASTNode* parse(Token* tokens) {
    int index = 0;

    // Create the root node for the 'for' loop
    ASTNode* root = create_node(1, tokens[index++].value); // 'for'

    // Create the node for the loop variable
    ASTNode* var_node = create_node(2, tokens[index++].value); // 'node'
    root->left = var_node;

    // Skip the 'in' token
    index++;

    // Create the node for the iterable
    ASTNode* iterable_node = create_node(3, tokens[index++].value); // 'graph'
    root->right = iterable_node;

    // Create the body node
    ASTNode* body_node = create_node(4, tokens[index++].value); // 'doSomething'
    root->body = body_node;

    // Create the argument node for the function call
    ASTNode* arg_node = create_node(5, tokens[index++].value); // 'node'
    body_node->left = arg_node;

    return root;
}

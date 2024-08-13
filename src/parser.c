#include "parser.h"

ASTNode* parse(Token* tokens) {
    // Simplified parsing logic
    // In a real implementation, this would be more complex
    ASTNode* root = malloc(sizeof(ASTNode));
    root->value = strdup("print");
    root->left = malloc(sizeof(ASTNode));
    root->left->value = strdup("x");
    root->left->left = NULL;
    root->left->right = NULL;
    root->right = NULL;

    return root;
}

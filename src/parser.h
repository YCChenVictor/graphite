#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

// Define the types of AST nodes
enum {
    NODE_LITERAL,
    NODE_VARIABLE,
    NODE_ASSIGNMENT,
    NODE_BINARY_OP,
    NODE_INVALID
};

// Define the ASTNode structure
typedef struct ASTNode {
    int type; // Node type
    union {
        int value; // For literals
        char* identifier; // For variables
        struct {
            struct ASTNode* left; // Left child
            struct ASTNode* right; // Right child
            char* operator; // Operator for binary operations
        };
    };
} ASTNode;

// Function declarations
ASTNode* create_ast_node(int type);
ASTNode* parse(Token* tokens);

#endif // PARSER_H

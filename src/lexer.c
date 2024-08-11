#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

// Function to create a new token
Token* create_token(int type, const char* value) {
    Token* token = (Token*)malloc(sizeof(Token));
    token->type = type;
    token->value = strdup(value); // Duplicate the string value
    return token;
}

// Function to tokenize the source code
Token* tokenize(const char* source_code) {
    const char* p = source_code; // Pointer to traverse the source code
    char buffer[256]; // Buffer to store token values
    int index = 0;

    while (*p != '\0') {
        // Skip whitespace
        while (isspace(*p)) {
            p++;
        }

        // Check for end of input
        if (*p == '\0') {
            return create_token(TOKEN_END, ""); // End token
        }

        // Handle identifiers and keywords
        if (isalpha(*p)) {
            index = 0;
            while (isalnum(*p)) {
                buffer[index++] = *p++;
            }
            buffer[index] = '\0';
            return create_token(TOKEN_IDENTIFIER, buffer);
        }

        // Handle numbers
        if (isdigit(*p)) {
            index = 0;
            while (isdigit(*p)) {
                buffer[index++] = *p++;
            }
            buffer[index] = '\0';
            return create_token(TOKEN_NUMBER, buffer);
        }

        // Handle operators (for simplicity, just single character operators)
        if (strchr("+-*/", *p)) {
            buffer[0] = *p++;
            buffer[1] = '\0';
            return create_token(TOKEN_OPERATOR, buffer);
        }

        // Invalid character handling
        buffer[0] = *p++;
        buffer[1] = '\0';
        return create_token(TOKEN_INVALID, buffer);
    }

    return create_token(TOKEN_END, ""); // End token at the end of input
}

// Function to free a token
void free_token(Token* token) {
    if (token) {
        free(token->value); // Free the duplicated string
        free(token); // Free the token structure
    }
}

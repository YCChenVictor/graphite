#include "tokenizer.h"

Token* tokenize(const char* input) {
    // Simplified tokenization logic
    // In a real implementation, this would be more complex
    Token* tokens = malloc(sizeof(Token) * 10); // Allocate space for 10 tokens
    int index = 0;

    // Example tokenization
    tokens[index++] = (Token){TOKEN_PRINT, strdup("print")};
    tokens[index++] = (Token){TOKEN_IDENTIFIER, strdup("x")};
    tokens[index++] = (Token){TOKEN_SEMICOLON, strdup(";")};
    tokens[index++] = (Token){TOKEN_EOF, NULL};

    return tokens;
}

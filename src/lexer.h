#ifndef LEXER_H
#define LEXER_H

enum {
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_OPERATOR,
    TOKEN_END,
    TOKEN_INVALID
};

typedef struct {
    int type;
    char* value;
} Token;

Token* tokenize(const char* source_code);

#endif

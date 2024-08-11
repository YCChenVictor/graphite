#ifndef LEXER_H
#define LEXER_H

typedef struct {
    int type;
    char* value;
} Token;

Token* tokenize(const char* source_code);

#endif

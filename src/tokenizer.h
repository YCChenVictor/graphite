#ifndef TOKENIZER_H
#define TOKENIZER_H

char** tokenize(const char* input);
void free_tokens(char** tokens);

typedef struct {
    char* value;
    // other fields...
} Token;

#endif // TOKENIZER_H

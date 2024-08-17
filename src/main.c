#include <stdio.h>
#include "main.h"

void process_file(const char* filename) {
    char* input = read_file(filename);

    Token *tokens = (Token *)(tokenize(input));
    // print_tokens(tokens);
    Program* ast = parse(tokens);
    // print_ast(ast);
    interpret(ast);

    // free(tokens);
    // free(ast);
}

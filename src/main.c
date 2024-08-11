#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"
#include "interpreter.h"

// Function to read the source code from a file
char* read_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Could not open file: %s\n", filename);
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = (char*)malloc(length + 1);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    fread(buffer, 1, length, file);
    buffer[length] = '\0';

    fclose(file);
    return buffer;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <source_file>\n", argv[0]);
        return 1;
    }

    // Read the source code from the file
    char* source_code = read_file(argv[1]);

    // Step 1: Lexical Analysis
    Token* tokens = tokenize(source_code);
    if (!tokens) {
        fprintf(stderr, "Lexical analysis failed\n");
        free(source_code);
        return 1;
    }

    // Step 2: Parsing
    ASTNode* ast = parse(tokens);
    if (!ast) {
        fprintf(stderr, "Parsing failed\n");
        free(tokens);
        free(source_code);
        return 1;
    }

    // Step 3: Interpretation / Code Execution
    interpret(ast);

    // Cleanup
    free_ast(ast);
    free(tokens);
    free(source_code);

    return 0;
}

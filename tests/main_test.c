// compile: gcc -o main_test main_test.c ../src/interpreter.c ../src/tokenizer.c ../src/parser.c
// run it: ./main_test

#include <stdio.h>
#include "../src/tokenizer.h"
#include "../src/parser.h"
#include "../src/interpreter.h"

void print_tokens(Token* tokens) {
    // Assuming tokens is an array terminated by a special token or NULL
    for (int i = 0; tokens[i].value != NULL; i++) {
        printf("Token: %s\n", tokens[i].value);
    }
}

void print_ast(ASTNode* node, int depth) {
    if (node == NULL) {
        return;
    }
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    printf("Node Type: %d, Value: %s\n", node->type, node->value);
    print_ast(node->left, depth + 1);
    print_ast(node->right, depth + 1);
    print_ast(node->body, depth + 1);
}

char* read_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file");
        return NULL;
    }

    // Get the file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate buffer to hold the file contents
    char* input = (char*)malloc(file_size + 1);
    if (input == NULL) {
        perror("Failed to allocate memory");
        fclose(file);
        return NULL;
    }

    // Read the file into the buffer
    fread(input, 1, file_size, file);
    input[file_size] = '\0'; // Null-terminate the string

    fclose(file);
    return input;
}

void test_for_loop_interpreter() {
    const char* filename = "for_loop_script.gh";
    char* input = read_file(filename);
    if (input != NULL) {
        printf("File content:\n%s\n", input);
    } else {
        printf("Failed to read file.\n");
    }

    Token *tokens = (Token *)(tokenize(input));
    print_tokens(tokens);
    // ASTNode* ast = parse(tokens);
    // interpret(ast);

    // free(tokens);
    // free(ast);
}

int main() {
    test_for_loop_interpreter();
    return 0;
}

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

void test_for_loop_interpreter() {
    const char* input = "for node in graph { print(node); }";
    Token *tokens = (Token *)(tokenize(input));
    ASTNode* ast = parse(tokens);
    interpret(ast);

    free(tokens);
    free(ast);
}

int main() {
    test_for_loop_interpreter();
    return 0;
}

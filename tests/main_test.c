// compile: gcc -o main_test main_test.c ../src/interpreter.c ../src/tokenizer.c ../src/parser.c
// run it: ./main_test

#include <stdio.h>
#include "../src/tokenizer.h"
#include "../src/parser.h"
#include "../src/interpreter.h"

void test_for_loop_interpreter() {
    const char* input = "for node in graph { doSomething(node); }";
    char** tokens = tokenize(input);

    int index = 0;
    while (tokens[index] != NULL) {
        printf("Token: %s\n", tokens[index]);
        index++;
    }
    free_tokens(tokens);
    // ASTNode* ast = parse(tokens);

    // interpret(ast); // engine

    // free(tokens);
    // free(ast);
}

int main() {
    test_for_loop_interpreter();
    return 0;
}

// compile: gcc -o main_test main_test.c ../src/interpreter.c ../src/tokenizer.c ../src/parser.c
// run it: ./main_test

#include "../src/tokenizer.h"
#include "../src/parser.h"
#include "../src/interpreter.h"

void test_for_loop_interpreter() {
    const char* input = "for (int i = 0; i < 10; i++) { print i; }";
    Token* tokens = tokenize(input);
    ASTNode* ast = parse(tokens);

    interpret(ast);

    // Clean up
    free(tokens);
    free(ast);
}

int main() {
    test_for_loop_interpreter();
    return 0;
}

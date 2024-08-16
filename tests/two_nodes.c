// compile: gcc -o two_nodes two_nodes.c ../src/interpreter.c ../src/tokenizer.c ../src/parser.c ../src/utils.c
// run it: ./two_nodes

// Start to implement unity
// #include "unity.h"
#include "../src/utils.h"
#include <stdio.h>

int main() {
    const char* filename = "../scripts/for_loop_two_node.gh";
    char* input = read_file(filename);

    Token *tokens = (Token *)(tokenize(input));
    // print_tokens(tokens);
    Program* ast = parse(tokens);
    // print_ast(ast);
    interpret(ast);

    // free(tokens);
    // free(ast);
    return 0;
}

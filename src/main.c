#include <stdio.h>
#include "tokenizer.h"
#include "parser.h"
#include "interpreter.h"

// Graph Representation
typedef struct GraphNode {
    char* value;
    struct GraphNode** children;
    int child_count;
} GraphNode;

int main() {
    const char* script = "print x;";
    Token* tokens = tokenize(script);
    // ASTNode* ast = parse(tokens);
    // GraphNode* graph = astToGraph(ast);
    // executeGraph(graph);

    // Free allocated memory (not shown for brevity)

    return 0;
}

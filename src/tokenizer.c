#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tokenizer.h"

// Token: node0
// Token: parent
// Token: node4
// Token: value
// Token: 0
// Token: node1
// Token: parent
// Token: node0
// Token: value
// Token: 1
// Token: node2
// Token: parent
// Token: node1
// Token: value
// Token: 2
// Token: node3
// Token: parent
// Token: node1
// Token: node2
// Token: value
// Token: 3
// Token: node4
// Token: parent
// Token: node1
// Token: node2
// Token: value
// Token: 4
// Token: for
// Token: node
// Token: in
// Token: node1
// Token: node4
// Token: print
// Token: node
// Token: value
char** tokenize(const char* input) {
    char delimiters[] = " {}();,.!?\"'\\/:[]<>@#$%^&*+-=|`~\t\n";
    char* input_copy = strdup(input); // Make a copy of the input string
    int token_count = 0;
    char* token = strtok(input_copy, delimiters);

    // First pass to count tokens
    while (token != NULL) {
        token_count++;
        token = strtok(NULL, delimiters);
    }

    // Allocate memory for tokens array
    char** tokens = (char**)malloc((token_count + 1) * sizeof(char*));
    strcpy(input_copy, input); // Reset input_copy
    token = strtok(input_copy, delimiters);
    int index = 0;

    // Second pass to store tokens
    while (token != NULL) {
        tokens[index] = strdup(token);
        index++;
        token = strtok(NULL, delimiters);
    }
    tokens[index] = NULL; // Null-terminate the array

    free(input_copy); // Free the copy of the input string
    return tokens;
}

void free_tokens(char** tokens) {
    int index = 0;
    while (tokens[index] != NULL) {
        free(tokens[index]);
        index++;
    }
    free(tokens);
}

// compile: gcc -o two_nodes two_nodes.c ../src/utils.c ../src/interpreter.c ../src/tokenizer.c ../src/parser.c -lunity
// run it: ./two_nodes

#include "../Unity/src/unity.h"
#include "../src/utils.h"

// Function prototype for process_file
void process_file(const char* filename);

void setUp(void) {
    // Set up code if needed
}

void tearDown(void) {
    // Clean up code if needed
}

void test_process_file(void) {
    const char* filename = "../scripts/for_loop_two_node.gh";
    process_file(filename);
    // Add assertions to verify the expected behavior
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_process_file);
    return UNITY_END();
}

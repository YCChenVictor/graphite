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
    
    // Redirect stdout to a buffer
    char buffer[128];
    memset(buffer, 0, sizeof(buffer));
    FILE* original_stdout = stdout;
    FILE* temp_stdout = fmemopen(buffer, sizeof(buffer), "w");
    stdout = temp_stdout;

    // Call the function
    process_file(filename);

    // Restore stdout
    fflush(stdout);
    stdout = original_stdout;
    fclose(temp_stdout);

    // Check the buffer for expected output
    TEST_ASSERT_NOT_NULL(strstr(buffer, "0"));
    TEST_ASSERT_NOT_NULL(strstr(buffer, "1"));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_process_file);
    return UNITY_END();
}

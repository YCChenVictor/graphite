#include "../Unity/src/unity.h"
#include "../src/main.h"

void setUp(void) {
    // Set up code if needed
}

void tearDown(void) {
    // Clean up code if needed
}

void test_two_nodes(void) {
    const char* filename = "../scripts/for_loop_two_nodes.gh";
    
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

void test_three_nodes(void) {
    const char* filename = "../scripts/for_loop_three_nodes.gh";
    
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
    TEST_ASSERT_NOT_NULL(strstr(buffer, "2"));
}

void test_tree_012_nodes(void) {
    const char* filename = "../scripts/for_loop_tree_012.gh";
    
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
    const char* expected_output = "0 1 2 ";
    TEST_ASSERT_EQUAL_STRING(expected_output, buffer);
}

void test_tree_013_nodes(void) {
    const char* filename = "../scripts/for_loop_tree_013.gh";
    
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
    const char* expected_output = "0 1 3 ";
    TEST_ASSERT_EQUAL_STRING(expected_output, buffer);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_two_nodes);
    RUN_TEST(test_three_nodes);
    RUN_TEST(test_tree_012_nodes);
    RUN_TEST(test_tree_013_nodes);
    return UNITY_END();
}

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

# Directories
SRC_DIR = src
TEST_DIR = test
BUILD_DIR = build
MAIN_DIR = main

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
TEST_FILES = $(wildcard $(TEST_DIR)/*.c)
MAIN_FILES = $(wildcard $(MAIN_DIR)/*.c)

# Output files
TEST_TARGET = $(BUILD_DIR)/test_runner
MAIN_TARGET = $(BUILD_DIR)/main_runner

# Unity framework
UNITY_DIR = Unity
UNITY_SRC = $(UNITY_DIR)/src/unity.c

# Ensure build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Build test target
$(TEST_TARGET): $(BUILD_DIR) $(SRC_FILES) $(TEST_FILES) $(UNITY_SRC)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(SRC_FILES) $(TEST_FILES) $(UNITY_SRC)

# Build main target
$(MAIN_TARGET): $(BUILD_DIR) $(SRC_FILES) $(MAIN_FILES)
	$(CC) $(CFLAGS) -o $(MAIN_TARGET) $(SRC_FILES) $(MAIN_FILES)

# Run tests
.PHONY: test
test: $(TEST_TARGET)
	cd build && ./test_runner

# Run main application
.PHONY: main
main: $(MAIN_TARGET)
	cd build && ./main_runner

# Clean build directory
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)/*

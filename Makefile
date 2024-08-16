# Makefile for running unit tests with Unity

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Directories
SRC_DIR = src
TEST_DIR = test
BUILD_DIR = build

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
TEST_FILES = $(wildcard $(TEST_DIR)/*.c)

# Output files
TARGET = $(BUILD_DIR)/test_runner

# Unity framework
UNITY_DIR = unity
UNITY_SRC = $(UNITY_DIR)/src/unity.c

# Ensure build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Build target
$(TARGET): $(SRC_FILES) $(TEST_FILES) $(UNITY_SRC)

# Run tests
.PHONY: test
test: $(TARGET)

# Clean build directory
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)/*

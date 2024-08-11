# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Source files in src/ directory
SRC = src/main.c src/lexer.c src/parser.c src/interpreter.c

# Object files
OBJ = $(SRC:.c=.o)

# Output executable
TARGET = graphite

# Default rule
all: $(TARGET)

# Rule to create the executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Rule to create object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJ) $(TARGET)

#!/bin/bash

# Define the path to the Graphite executable
GRAPHITE_EXEC="./graphite"

# Define the path to the example source file
SOURCE_FILE="../examples/sample.gph"

# Define the expected output
EXPECTED_OUTPUT="Node A created.
Node B created.
Edge A -> B created."

# Run the Graphite executable with the sample source file
OUTPUT=$($GRAPHITE_EXEC $SOURCE_FILE)

# Compare the actual output with the expected output
if [ "$OUTPUT" == "$EXPECTED_OUTPUT" ]; then
    echo "Test passed: Output matches expected output."
    exit 0
else
    echo "Test failed: Output does not match expected output."
    echo "Expected:"
    echo "$EXPECTED_OUTPUT"
    echo "Got:"
    echo "$OUTPUT"
    exit 1
fi

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Wconversion --coverage

# Include paths for Unity and headers
LDFLAGS = \
-I../unity \
-I../inc

# Source files and test file
SRC = $(wildcard ../src/*.c) ../unity/unity.c
TEST = test_baseXLib.c
OUT = test_baseXLib

# Default target
all: build

# Build the test executable
build:
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(OUT) $(SRC) $(TEST)

# Run the test executable
test: build
	./$(OUT)

# Generate code coverage report
coverage: test
	lcov --capture --directory . --output-file coverage.info
	lcov --ignore-errors unused --remove coverage.info '/tests/*' '/unity/*' --output-file coverage_filtered.info
	genhtml coverage_filtered.info --output-directory coverage_report

# Clean build artifacts and coverage files
clean:
	rm -f $(OUT) *.gcda *.gcno *.info
	rm -rf coverage_report

# Declare phony targets to avoid conflicts with files of the same name
.PHONY: all build test coverage clean
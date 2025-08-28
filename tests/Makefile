CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -Wconversion --coverage
LDFLAGS= \
-I../unity\
-I../inc

SRC=$(wildcard ../src/*.c) ../unity/unity.c
TEST=test_baseXLib.c
OUT=test_baseXLib

all: build

build:
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(OUT) $(SRC) $(TEST)

test: build
	./$(OUT)

coverage: test
	lcov --capture --directory . --output-file coverage.info
	lcov --ignore-errors unused --remove coverage.info '/tests/*' '/unity/*' --output-file coverage_filtered.info
	genhtml coverage_filtered.info --output-directory coverage_report

clean:
	rm -f $(OUT) *.gcda *.gcno *.info
	rm -rf coverage_report
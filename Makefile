CXX ?= c++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -Wpedantic -Iinclude
CC ?= cc
CFLAGS ?= -std=c17 -Wall -Wextra -Wpedantic -Iinclude

SOURCES := $(shell find src -name '*.cpp')
LIB_SOURCES := $(filter-out src/main.cpp,$(SOURCES))
TEST_SOURCES := $(shell find tests -name '*.cpp')
TEST_BINS := $(patsubst tests/%.cpp,build/tests/%,$(TEST_SOURCES))
C_SOURCES := $(shell find src -name '*.c')
C_OBJECTS := $(patsubst src/%.c,build/objects/%.o,$(C_SOURCES))

.PHONY: math run test clean

math: $(SOURCES) $(C_OBJECTS)
	$(CXX) $(CXXFLAGS) $(SOURCES) $(C_OBJECTS) -o $@

run: math
	./math

test: $(TEST_BINS)
	for test_binary in $(TEST_BINS); do $$test_binary; done

build/tests/%: tests/%.cpp $(LIB_SOURCES) $(C_OBJECTS)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(LIB_SOURCES) $< $(C_OBJECTS) -o $@

build/objects/%.o: src/%.c include/linear_algebra/linear_algebra.h
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f math $(TEST_BINS) $(C_OBJECTS)

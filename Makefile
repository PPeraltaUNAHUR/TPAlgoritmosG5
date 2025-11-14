CXX := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra

ROOT := $(abspath .)
BUILD_DIR := $(ROOT)/build
THIRD_PARTY := $(ROOT)/third_party

SRC_DIR := $(ROOT)/src
TEST_SRC := $(SRC_DIR)/tests/test_tabla.cpp
LIB_SRCS := $(SRC_DIR)/structures/TablaHash.cpp \
            $(SRC_DIR)/models/Centro.cpp

TEST_BIN := $(BUILD_DIR)/tests_hash

.PHONY: all build test clean

all: build

build: $(TEST_BIN)

$(TEST_BIN): $(TEST_SRC) $(LIB_SRCS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

test: build
	$(TEST_BIN)

clean:
	rm -rf $(BUILD_DIR)



CXX := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra

ROOT := $(abspath .)
BUILD_DIR := $(ROOT)/build
THIRD_PARTY := $(ROOT)/third_party

SRC_DIR := $(ROOT)/src
TEST_SRC := $(SRC_DIR)/tests/test_tabla.cpp
LIB_SRCS := $(SRC_DIR)/structures/TablaHash.cpp \
            $(SRC_DIR)/models/Centro.cpp \
            $(SRC_DIR)/models/Envio.cpp \
            $(SRC_DIR)/models/Paquete.cpp \
            $(SRC_DIR)/models/Camino.cpp \
            $(SRC_DIR)/models/Arista.cpp \
            $(SRC_DIR)/utils/Fecha.cpp \
            $(SRC_DIR)/graph/Grafo.cpp \
            $(SRC_DIR)/core/SistemaLogistica.cpp \
            $(SRC_DIR)/core/Backtracking.cpp

TEST_BIN := $(BUILD_DIR)/tests_hash
APP_BIN := $(BUILD_DIR)/app
APP_SRCS := $(SRC_DIR)/main.cpp $(LIB_SRCS)

.PHONY: all build test clean app run

all: app

build: $(TEST_BIN)

$(TEST_BIN): $(TEST_SRC) $(LIB_SRCS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

test: build
	$(TEST_BIN)

app: $(APP_BIN)

$(APP_BIN): $(APP_SRCS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

run: app
	$(APP_BIN)

clean:
	rm -rf $(BUILD_DIR)



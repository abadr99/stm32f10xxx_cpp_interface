# =====================================================================
# Makefile for Unit Tests and Coverage Analysis
# =====================================================================

# -------------------------------
# Configuration
# -------------------------------

# Paths for Google Test (Windows-specific case)
GTEST_INC ?= "C:/Program Files (x86)/googletest-distribution/include"
GTEST_LIB ?= ../googletest/build/lib/libgtest.a ../googletest/build/lib/libgtest_main.a

# Include directories for source files
U_INC := -I../dev -I../dev/inc

# Test coverage directories and tools
MCAL_DIR := ../dev/src/mcal
COVERAGE_OUT := coverage.info
GENERATE_HTML_OUT := html

# Coverage tool configurations
COVERAGE_TOOL := lcov
COVERAGE_TOOL_OPT := --capture --directory $(MCAL_DIR) --output-file temp.info

GENERATE_HTML := genhtml

# Linter path
LINT_PATH := ../tools/cppliny.py

# -------------------------------
# Compiler Settings
# -------------------------------

U_CXX := g++
U_CXX_OPT := -std=c++17 -Wall -Wextra -g -DUNIT_TEST -fprofile-arcs -ftest-coverage

# Define target and linker flags based on OS
ifeq ($(OS),Windows_NT)
    U_TARGET := unittests/unittests.exe
    U_LD := $(GTEST_LIB)
    U_INC += -I$(GTEST_INC)
else
    U_TARGET := unittests/unittests.elf
    U_LD := -lgtest -lpthread
endif

# -------------------------------
# Sources and Objects
# -------------------------------

# Source directories
U_SRCS_DIRS := ./unittests ../dev/src

# Locate all C++ source files
U_SRC := $(shell find $(U_SRCS_DIRS) -type f -name "*.cpp")

# Convert source files to object files
U_OBJ := $(U_SRC:.cpp=.o)

# Locate MCAL source files for coverage analysis
MCAL_SRC := $(shell find $(MCAL_DIR) -type f -name "*.cpp")

# -------------------------------
# Targets
# -------------------------------

# Linting target
.PHONY: cpplint
cpplint:
	@echo "[Makefile]: Running linter..."
	@python3 $(LINT_PATH) --recursive .
	@echo "[Makefile]: Linting completed."

# Build the unit tests
.PHONY: build-unittests
build-unittests: $(U_OBJ)
	@echo "[Makefile]: Building unit tests..."
	@$(U_CXX) $(U_CXX_OPT) $(U_OBJ) $(U_INC) $(U_LD) -o $(U_TARGET)
	@echo "[Makefile]: Build completed successfully."

# Rule for compiling individual object files
%.o: %.cpp
	@echo "[Makefile]: Compiling $<..."
	@$(U_CXX) $(U_CXX_OPT) $(U_INC) -c $< -o $@
	@echo "[Makefile]: Compilation of $< completed."

# Run the unit tests
.PHONY: run-unittests
run-unittests: build-unittests
	@echo "[Makefile]: Running unit tests..."
	@./$(U_TARGET)

# Generate test coverage reports
.PHONY: test-coverage
test-coverage:
	@echo "[Makefile]: Generating test coverage report..."
	@$(COVERAGE_TOOL) $(COVERAGE_TOOL_OPT)
	@$(COVERAGE_TOOL) --remove temp.info '/usr/*' --output-file $(COVERAGE_OUT)
	@rm -f temp.info
	@echo "[Makefile]: Generating HTML coverage report..."
	@$(GENERATE_HTML) $(COVERAGE_OUT) --output-directory $(GENERATE_HTML_OUT)

# Clean up build artifacts and coverage files
.PHONY: clean
clean:
	@echo "[Makefile]: Cleaning up..."
	@rm -f $(U_OBJ) $(U_TARGET)
	@rm -f $(MCAL_DIR)/*.gcda $(MCAL_DIR)/*.gcno $(COVERAGE_OUT)
	@rm -rf $(GENERATE_HTML_OUT)
	@echo "[Makefile]: Clean completed."

# Default target
.PHONY: all
all: build-unittests

# Variables
LINT_PATH := ../tools/cppliny.py

U_CXX := g++
U_CXX_OPT := -std=c++17 -Wall -Wextra -g -DUNIT_TEST

# Find source files in 'unittests' and specific 'dev' directories
U_SRCS_DIRS := ./unittests ../dev/src
U_SRC := $(shell find $(U_SRCS_DIRS) -type f -name "*.cpp")

U_OBJ := $(U_SRC:.cpp=.o)

U_TARGET := unittests/unittests.elf
U_LD := -lgtest -lpthread
U_INC := -I../dev -I../dev/inc/

# Linting
cpplint:
	@python3 $(LINT_PATH) --recursive .

# Build target
build-unittests: $(U_OBJ)
	@$(U_CXX) $(U_CXX_OPT) $(U_OBJ) $(U_LD) -o $(U_TARGET)
	@echo "[MAKEFILE]: Build Successfully ..."

# Rule for creating object files
%.o: %.cpp
	@$(U_CXX) $(U_CXX_OPT) $(U_INC) -c $< -o $@
	@echo "[Makefile][Unittest]: Done compiling $<"

# Run the unit tests
run-unittests:
	./$(U_TARGET)

# Clean up
clean:
	@rm -rf $(U_OBJ)
	@rm -rf $(U_TARGET)

# Variables
LINT_PATH := ../tools/cppliny.py

U_CXX := g++
U_CXX_OPT := -std=c++17 -Wall -Wextra -g -DUNIT_TEST -fprofile-arcs -ftest-coverage

# Find source files in 'unittests' and specific 'dev' directories
U_SRCS_DIRS := ./unittests ../dev/src
U_SRC := $(shell find $(U_SRCS_DIRS) -type f -name "*.cpp")

U_OBJ := $(U_SRC:.cpp=.o)

U_TARGET := unittests/unittests.elf
U_LD := -lgtest -lpthread 

U_INC := -I../dev -I../dev/inc/
ifeq ($(OS),Windows_NT)
U_INC += -I"$env:USERPROFILE\vcpkg\installed\x64-windows\include" -L"$env:USERPROFILE\vcpkg\installed\x64-windows\lib"
endif

# ---- TEST COVERAGE
# note: For now we are intersted in mcal only
MCAL_DIR = ../dev/src/mcal
MCAL_SRC = $(shell find $(MCAL_DIR) -type f -name "*.cpp")
COVERAGE_OUT  = coverage.info
COVERAGE_TOOL = lcov
COVERAGE_TOOL_OPT = --capture --directory $(MCAL_DIR) --output-file temp.info
GENERATE_HTML = genhtml
GENERATE_HTML_OUT = html

# Linting
cpplint:
	@python3 $(LINT_PATH) --recursive .

# Build target
build-unittests: $(U_OBJ)
	$(U_CXX) $(U_CXX_OPT) $(U_OBJ) $(U_LD) -o $(U_TARGET)
	@echo "[MAKEFILE]: Build Successfully ..."

# Rule for creating object files
%.o: %.cpp
	$(U_CXX) $(U_CXX_OPT) $(U_INC) -c $< -o $@
	@echo "[Makefile][Unittest]: Done compiling $<"

# Run the unit tests
run-unittests:
	@./$(U_TARGET)

test-coverage:
	@echo "[Makefile][Unittest]: Running test coverage"
	@$(COVERAGE_TOOL) $(COVERAGE_TOOL_OPT)
	@$(COVERAGE_TOOL) --remove temp.info '/usr/*' --output-file $(COVERAGE_OUT)
	@rm -rf temp.info
	@echo "[Makefile][Unittest]: Generating html files"
	@$(GENERATE_HTML) $(COVERAGE_OUT) --output-directory $(GENERATE_HTML_OUT)

# Clean up
clean:
	@rm -rf $(U_OBJ)
	@rm -rf $(U_TARGET)
	@rm -rf $(MCAL_DIR)/*.gcda $(MCAL_DIR)/*.gcno $(COVERAGE_OUT) 
	@rm -rf $(COVERAGE_DIR_OPT)

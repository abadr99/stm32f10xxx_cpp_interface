# TODO(@abadr99): Set dependencies (i.e. don't compile unmodifed files again)

LINT_PATH:= ../tools/cppliny.py

U_CXX:= g++
U_CXX_OPT := -std=c++17 -Wall -Wextra -g

U_SRCS_DIR := $(shell find ./unittests -maxdepth 5 -type d)
U_SRC:= $(foreach S,$(U_SRCS_DIR),$(wildcard $(S)/*.cpp))

U_SRCS_DIR := $(shell find ../dev -maxdepth 5 -type d | grep -E '\../dev/hal/|\../dev/mcal/|\../dev/utils/')
U_SRC+= $(foreach S,$(U_SRCS_DIR),$(wildcard $(S)/*.cpp))

U_TARGET := unittests/unittests.elf
U_LD := -lgtest -lpthread 
U_INC := -I../dev

cpplint:
	@python3 $(LINT_PATH)  --recursive .

build-unittests:
	$(U_CXX) $(U_CXX_OPT) $(U_SRC) $(U_LD) $(U_INC) $(U_OBJ) -o $(U_TARGET)
	@echo "[MAKEFILE]: Build Successfully ..."

run-unittests:
	./$(U_TARGET)

debug:
	echo $(U_SRC)

clean:
	rm -rf unittests/*.elf
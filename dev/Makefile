INPUT_FILE ?= ./build/modules.in
DIRS := ./mcal ./hal ./utils
SOURCES := $(shell python3 ./build/Parser.py --file "$(INPUT_FILE)")
SOURCES += $(wildcard ./utils/src/*.cpp) # ALl utils should be added with all modules
SRC_NAMES:= $(notdir $(SOURCES))
SOURCES_COUNT:= $(words $(SOURCES))
SOURCES_CTR:=0
INC:=  -I. -I./mcal/inc/ -I./hal/inc/ -I./utils/inc/
LINT_PATH:= ../tools/cppliny.py

HW_TEST_PATH= ../tests/hardware
HW_MAINS=$(shell find $(HW_TEST_PATH) -name "*.cpp")


# ---------------------------------------------------------------
# compile
# This function compiles a given source file into an ELF file 
# and then converts that ELF file into a HEX file. 
# It uses three arguments to perform the compilation and conversion.
#
# Parameters:
# $1 - The source file to be compiled (e.g., ./main.cpp).
# $2 - The output directory where the ELF and HEX files will be saved.
# $3 - The base name for the ELF and HEX output files (e.g., 'stm').
#
# ---------------------------------------------------------------
define compile 
	$(CXX) $(CXX_FLAGS)  $(INC) $(OBJS) $(STARTUPOBJ_PATH) $(1) $(LDFLAGS) -T build/$(MCU).ld -o $(2)/$(3).elf
	$(OBJ_COPY) $(OBJ_COPY_OPTS) $(2)/$(3).elf $(2)/$(3).hex
endef

include build/stm32.mk

.PHONY: all clean build build-opt cpplint build-hw clean-hw

all:build

cpplint:
	@python3 $(LINT_PATH)  --recursive .

# ------------------------------------------
# Rule to build for debug and test mode 
# make build
# ------------------------------------------
build: $(OBJS) 
	@$(call compile,./main.cpp,./,$(TARGET))
	@echo "\n[Makefile][build] : Compiled successfully."

# ------------------------------------------
# Rule to build for HW Tests 
# make build-hw 					---> TO BUILD **ALL** 	   HARDWARE TESTS 
# make build-hw FILTER=path/to/test ---> TO BUILD **SPECIFIC** HARDWARE TEST
# e.g. make -C ./dev/ build-hw FILTER=../tests/hardware-app/mcal/gpio/main.cpp
# Note:
# The expression $(notdir $(patsubst %/,%,$(dir $(HW_FILTER)))) in the rule
# 	is a combination of functions used to extract the base directory name from a file path.
# ------------------------------------------
build-hw: $(OBJS)
ifneq ($(FILTER), )
	@$(call compile,$(FILTER),$(shell dirname $(FILTER)),$(notdir $(patsubst %/,%,$(dir $(FILTER)))))
	@echo "\n[Makefile]: note: Filter compilation $(FILTER)"
	@echo "\n[Makefile]: Compiling $(dir $(FILTER)) successfully"
else 
	@$(foreach FILE,$(HW_MAINS), echo "[Makefile][HW-Test]: $(FILE)"; $(call compile,$(FILE),$(dir $(FILE)),$(basename $(notdir $(FILE))));)
	@echo "\n[Makefile]: Compiled successfully."
endif

clean-hw:
	@find $(HW_TEST_PATH) \( -name '*.elf' -o -name '*.hex' \) -exec rm -rf {} +
	@echo "\n[Makefile]: Cleaning successfully."
	
# ------------------------------------------
# Rule to build for real applications
# make opt-build
# ------------------------------------------
build-opt: $(OBJS) 
	$(CXX) $(OPT_CXX_FLAGS) $(OBJS) $(STARTUP_PATH) ./main.cpp -o $(ELF_TARGET)
	@echo "\n[Makefile][opt-build] : Compiled successfully."	

# ------------------------------------------
# Rule to upload hex file to mcu
# make upload
# ------------------------------------------
upload:
	$(FLASH) write $(HEX_TARGET) 0x08000000 

clean:
	@rm -rf *.o
	@rm -rf *.bin
	@rm -rf *.exe
	@rm -rf *.elf
	@rm -rf *.hex
	@rm -rf *.map
	@rm -rf .build
	@rm -rf build.map

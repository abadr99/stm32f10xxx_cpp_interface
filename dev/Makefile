PYTHON ?= python3

USE_FREERTOS ?= 0

# --- BUILD
INPUT_FILE ?= ./build/modules.in
SOURCES := $(shell $(PYTHON) ./build/Parser.py --file "$(INPUT_FILE)")
SOURCES += $(wildcard ./src/utils/*.cpp) # ALl utils should be added with all modules
SRC_NAMES:= $(notdir $(SOURCES))
SOURCES_COUNT:= $(words $(SOURCES))
SOURCES_CTR:=0
INC:=  -I. -I./inc/ -I./lib/
LIB_DIR := ./lib
LIB_NAME := stm32f103cpp.a
FREE_RTOS_SRC_DIR := ./lib//src
STARTUP_CODE := ./src/mcal/stm32f103_startup.cpp

ifeq ($(USE_FREERTOS),1)
	FREE_RTOS_LIB := ./lib/freeRTOS/libfreertos.a
	C_SOURCES := $(wildcard $(FREE_RTOS_SRC_DIR)/*.c)
	C_SRC_NAMES:= $(notdir $(C_SOURCES))
	SOURCES_COUNT := $(shell echo $$(($(SOURCES_COUNT) + $(words $(C_SOURCES)))))
endif

# --- LINTER
LINT_PATH:= ../tools/cppliny.py --exclude=lib/freeRTOS/*.h

# --- HARDWARE TESTS
# TODO(@mrefat): Move this to tests/Makefile 
HW_TEST_PATH= ../tests/hardware
HW_MAINS=$(shell find $(HW_TEST_PATH) -name "*.cpp")

# --- DOXYGEN
DOXYFILE := ../doxy/conf
DOXYGEN_OUTPUT := ../doxy/html

CXX_FLAGS += -MDD -MP
OBJS := $(SOURCES:.cpp=.o)
DEPS :=$(OBJS:.o=.d)
-include $(DEPS)
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
# $4 - Path to the startup code file 
#
# ---------------------------------------------------------------
define compile 
	$(ARM_CXX) $(CXX_FLAGS) $(INC) $(CXX_OBJS)  $(4) $(1) $(LDFLAGS) -T build/$(MCU).ld  $(FREE_RTOS_LIB) -o $(2)/$(3).elf
	$(OBJ_COPY) $(OBJ_COPY_OPTS) $(2)/$(3).elf $(2)/$(3).hex
endef

include build/stm32.mk

.PHONY: all clean build build-opt cpplint build-hw clean-hw

all:build

cpplint:
	@$(PYTHON) $(LINT_PATH)  --recursive .

# ------------------------------------------
# Rule to build for debug and test mode 
# make build
# ------------------------------------------
build: $(CXX_OBJS) 
	$(call compile, ./main.cpp,.,$(TARGET),$(STARTUP_CODE))
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
build-hw: $(CXX_OBJS)
ifneq ($(FILTER), )
	@$(call compile,$(FILTER),$(shell dirname $(FILTER)),$(notdir $(patsubst %/,%,$(dir $(FILTER)))))
	@echo "\n[Makefile]: note: Filter compilation $(FILTER)"
	@echo "\n[Makefile]: Compiling $(dir $(FILTER)) successfully"
else 
	@$(foreach FILE,$(HW_MAINS), echo "[Makefile][HW-Test]: Done compiling $(FILE)"; $(call compile,$(FILE),$(dir $(FILE)),$(basename $(notdir $(FILE))));)
	@echo "\n[Makefile][HW-Test]: Compiled successfully."
endif

clean-hw:
	@find $(HW_TEST_PATH) \( -name '*.elf' -o -name '*.hex' \) -exec rm -rf {} +
	@echo "\n[Makefile]: Cleaning successfully."
	
# ------------------------------------------
# Rule to build for real applications
# make opt-build
# ------------------------------------------
build-opt: $(OBJS) 
	@$(ARM_CXX) $(OPT_CXX_FLAGS) $(INC)  $(OBJS) $(STARTUP_CODE) $(FREE_RTOS_LIB) ./main.cpp $(LDFLAGS) -T build/$(MCU).ld -o $(ELF_TARGET)
	@$(OBJ_COPY) $(OBJ_COPY_OPTS) $(ELF_TARGET) $(HEX_TARGET)
	@echo "\n[Makefile][opt-build] : Compiled successfully."	

# ---------------------------------------------
# Rule to create a lib
# ---------------------------------------------
gen-lib:$(CXX_OBJS) $(C_OBJS)
	@ar rcs $(LIB_NAME) $(CXX_OBJS) $(C_OBJS)

# ------------------------------------------
# Rule to upload hex file to mcu
# make upload
# ------------------------------------------
upload:
	$(FLASH) write $(HEX_TARGET) 0x08000000 

# ------------------------------------------
# Rule to generate Doxygen documentation
# make doxygen
# ------------------------------------------
doxygen:
	@echo "Generating Doxygen documentation..."
	@doxygen $(DOXYFILE)

# ------------------------------------------
# Rule to clean up Doxygen output
# make clean-doxygen
# ------------------------------------------
clean-doxygen:
	@echo "Cleaning Doxygen output..."
	@rm -rf $(DOXYGEN_OUTPUT)

# ----------------------------------------------
# Rule to generate FreeRTOS lib
# make gen-freertos-lib
# Note: remember before generating the library
#        to edit FREE_RTOS_SRC_DIR in this 
#        Makefile and make sure it points to 
#        the correct FreeRTOS source directory.
# ----------------------------------------------
gen-freertos-lib: $(C_OBJS)
	@ar rcs $(FREE_RTOS_LIB)  $(C_OBJS)
	@echo "\n[Makefile][Dev]: Generated FreeRTOS lib files successfully."

# ------------------------------------------
# Rule to clean up build files
# make clean
# ------------------------------------------
clean:
	@rm -rf *.o
	@rm -rf *.bin
	@rm -rf *.exe
	@rm -rf *.elf
	@rm -rf *.hex
	@rm -rf *.map
	@rm -rf .build
	@rm -rf build.map
	@rm -rf $(OBJDIR)/*.d

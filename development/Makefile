INPUT_FILE ?= ./modules.in
DIRS := ./mcal ./hal ./utils
SOURCES := $(shell sed 's/$$/.cpp/' "$(INPUT_FILE)")
SOURCES += $(wildcard ./development/utils/src/*.cpp) # ALl utils should be added with all modules
SRC_NAMES:= $(notdir $(SOURCES))
SOURCES_COUNT:= $(words $(SOURCES))
SOURCES_CTR:=0
INC:=  $(foreach dir,$(DIRS), -I$(dir)/inc)

include stm32.mk

.PHONY: all clean build build-opt 

all:build

build: build
# ------------------------------------------
# Rule to build avr for debug and test mode 
# make build
# ------------------------------------------
build: $(OBJS) 
	@$(GCC) $(GCCFLAGS) $(OBJS) ./main.cpp -o $(ELF_TARGET)
	@$(OBJ_COPY) $(OBJ_COPY_OPTS) $(ELF_TARGET) $(HEX_TARGET)
	@echo "\n[Makefile][build] : Compiled successfully."

# ------------------------------------------
# Rule to build avr for real applications
# make opt-build
# ------------------------------------------
build-opt: $(OBJS) 
	@$(GCC) $(OPT_CCFLAGS) $(OBJS) ./main.cpp -o $(ELF_TARGET)
	@$(OBJ_COPY) $(OBJ_COPY_OPTS) $(ELF_TARGET) $(HEX_TARGET)
	@echo "\n[Makefile][opt-build] : Compiled successfully."	

clean:
	@find . -name "*.o" -type f -delete
	@rm -rf .build
	@rm -rf *.o
	@rm -rf *.bin
	@rm -rf *.exe
	@rm -rf *.elf
	@rm -rf *.hex
	@rm -rf avr
	@rm -rf .build
	@find . -name "*.o" -type f -delete
	@find tests/hardware/ -name "*.elf" -type f -delete
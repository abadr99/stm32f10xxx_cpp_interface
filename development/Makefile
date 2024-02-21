INPUT_FILE ?= ./build/modules.in
DIRS := ./mcal ./hal ./utils
SOURCES := $(shell cat "$(INPUT_FILE)")
SOURCES += $(wildcard ./development/utils/src/*.cpp) # ALl utils should be added with all modules
SRC_NAMES:= $(notdir $(SOURCES))
SOURCES_COUNT:= $(words $(SOURCES))
SOURCES_CTR:=0
INC:=  $(foreach dir,$(DIRS), -I$(dir)/inc)

include build/stm32.mk

.PHONY: all clean build build-opt 

all:build

# ------------------------------------------
# Rule to build for debug and test mode 
# make build
# ------------------------------------------
build: $(OBJS) 
	$(CXX) $(CXX_FLAGS) $(OBJS) ./main.cpp $(LDFLAGS) -T build/$(MCU).ld -o $(ELF_TARGET)
	@echo "\n[Makefile][build] : Compiled successfully."

# ------------------------------------------
# Rule to build for real applications
# make opt-build
# ------------------------------------------
build-opt: $(OBJS) 
	@$(CXX) $(OPT_CXX_FLAGS) $(OBJS) ./main.cpp -o $(ELF_TARGET)
	@echo "\n[Makefile][opt-build] : Compiled successfully."	

clean:
	@rm -rf *.o
	@rm -rf *.bin
	@rm -rf *.exe
	@rm -rf *.elf
	@rm -rf *.hex
	@rm -rf .build

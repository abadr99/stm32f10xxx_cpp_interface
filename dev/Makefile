INPUT_FILE ?= ./build/modules.in
DIRS := ./mcal ./hal ./utils
SOURCES := $(shell cat "$(INPUT_FILE)")
SOURCES += $(wildcard ./utils/src/*.cpp) # ALl utils should be added with all modules
SRC_NAMES:= $(notdir $(SOURCES))
SOURCES_COUNT:= $(words $(SOURCES))
SOURCES_CTR:=0
INC:=  -I. -I./mcal/inc/ -I./hal/inc/ -I./utils/inc/
LINT_PATH:= ../tools/cppliny.py

include build/stm32.mk

.PHONY: all clean build build-opt 

all:build

cpplint:
	@python3 $(LINT_PATH)  --recursive .

# ------------------------------------------
# Rule to build for debug and test mode 
# make build
# ------------------------------------------
build: $(OBJS) 
	$(CXX) $(CXX_FLAGS) $(OBJS) $(STARTUPOBJ_PATH) ./main.cpp $(LDFLAGS) -T build/$(MCU).ld -o $(ELF_TARGET)
	$(OBJ_COPY) $(OBJ_COPY_OPTS) $(ELF_TARGET) $(HEX_TARGET)
	@echo "\n[Makefile][build] : Compiled successfully."

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
	@rm -rf .build
	@rm -rf build.map
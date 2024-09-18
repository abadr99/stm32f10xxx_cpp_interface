INPUT_FILE ?= ./build/modules.in
DIRS := ./mcal ./hal ./utils
SOURCES := $(shell python3 ./build/Parser.py --file "$(INPUT_FILE)")
SOURCES += $(wildcard ./utils/src/*.cpp) # ALl utils should be added with all modules
SRC_NAMES:= $(notdir $(SOURCES))
SOURCES_COUNT:= $(words $(SOURCES))
SOURCES_CTR:=0
INC:=  -I. -I./mcal/inc/ -I./hal/inc/ -I./utils/inc/
LINT_PATH:= ../tools/cppliny.py

HW_TEST_PATH='../tests/hardware-app'
HW_MAINS=$(shell find $(HW_TEST_PATH) -name "*.cpp")



define compile 
	$(CXX) $(CXX_FLAGS)  $(INC) $(OBJS) $(STARTUPOBJ_PATH) $1 $(LDFLAGS) -T build/$(MCU).ld -o $2/$(ELF_TARGET)
	$(OBJ_COPY) $(OBJ_COPY_OPTS) $2/$(ELF_TARGET) $2/$(HEX_TARGET)
	@echo "\n[Makefile][build][$1] : Compiled successfully."
endef

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
	@$(call compile,./main.cpp,./)

# ------------------------------------------
# Rule to build for HW Tests 
# make build-hw
# ------------------------------------------
build-hw: $(OBJS)
	@$(foreach FILE,$(HW_MAINS), $(call compile,$(FILE),$(dir $(FILE))) ;)

# ------------------------------------------
# Rule to build for a specific HW Test
# make build HW_FILTER=
# ------------------------------------------
build-hw-filter: $(OBJS) 
	@$(call compile,$(HW_FILTER),$(shell dirname $(HW_FILTER)))
	
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

clean-hw:
	@for FILE in $(HW_MAINS) ; do \
    	DIR=$$(dirname $$FILE);\
		rm -f $$DIR/*.elf $$DIR/*.hex; \
	done



print:
	$(foreach FILE,$(HW_MAINS),echo $(dir $(FILE)))
GCC:= arm-none-eabi-g++
MCU:= atmega32a
CLK:= 8000000
OBJ_COPY:= avr-objcopy
GCCFLAGS:=    	 -g -Wall -DF_CPU=$(CLK) -mmcu=$(MCU) -gdwarf-2 -O2 -Werror -std=c++17
OPT_CCFLAGS:= 	 -g -Wall -DF_CPU=$(CLK) -mmcu=$(MCU) -gdwarf-2 -O3 -Werror -std=c++17
GCC_TEST_FLAGS:= -g -Wall -DF_CPU=$(CLK) -mmcu=$(MCU) -gdwarf-2 -O2 -Werror -std=c++17
OBJ_COPY_OPTS:= -j .text -j .data -O ihex 

TARGET:= avr
OBJDIR := .build/obj
OBJS:= $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRC_NAMES))


HEX_TARGET:= $(TARGET).hex
ELF_TARGET:=$(TARGET).elf


upload: $(HEX)
	@echo "NOT-SUPPORTED"

$(OBJDIR)/%.o : **/src/%.cpp
	@mkdir -p $(OBJDIR)
	@$(GCC) $(GCCFLAGS) $(INC) -c $< -o $@
	@$(eval SOURCES_CTR=$(shell echo $$(($(SOURCES_CTR)+1))))
	@echo "[Makefile] : [$(SOURCES_CTR)/$(words $(SOURCES))] $<"
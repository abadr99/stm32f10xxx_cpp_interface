CXX:= arm-none-eabi-g++
MCU:= stm32f103c8t6
CLK:= 8000000
CPU:= cortex-m3 

CXX_FLAGS:=   	 	 -mthumb -g -Wall -mcpu=$(CPU) -O0 -Werror -std=c++17 -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F10X_MD -DHSE_VALUE=8000000
OPT_CXX_FLAGS:= 	 -mthumb -g -Wall -mcpu=$(CPU) -O3 -Werror -std=c++17
CXX_TEST_FLAGS:=	 -mthumb -g -Wall -mcpu=$(CPU) -O2 -Werror -std=c++17
LDFLAGS = -Wl,--gc-sections,-Map=$@.map,-cref,-u,Reset_Handler

TARGET:= stm32
OBJDIR := .build/obj
OBJS:= $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRC_NAMES))


HEX_TARGET:= $(TARGET).hex
ELF_TARGET:=$(TARGET).elf


upload: $(HEX)
	@echo "NOT-SUPPORTED"

$(OBJDIR)/%.o : **/src/%.cpp
	mkdir -p $(OBJDIR)
	$(CXX) $(CXX_FLAGS) $(INC) -c $< -o $@
	@$(eval SOURCES_CTR=$(shell echo $$(($(SOURCES_CTR)+1))))
	@echo "[Makefile] : [$(SOURCES_CTR)/$(words $(SOURCES))] $<"

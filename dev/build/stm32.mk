CXX:= arm-none-eabi-g++
OBJ_COPY:= arm-none-eabi-objcopy
MCU:= stm32f103c8t6
CLK:= 8000000
CPU:= cortex-m3 

CXX_FLAGS:=   	 	 -mthumb -g -Wall -mcpu=$(CPU) -O0 -Werror -std=c++17 -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -flto -ffreestanding  -fno-exceptions -fno-move-loop-invariants -Wall -Wextra -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F10X_MD -DHSE_VALUE=8000000 --specs=rdimon.specs -lgcc -lc -lm -lrdimon 
OPT_CXX_FLAGS:= 	 -mthumb -g -Wall -mcpu=$(CPU) -O3 -Werror -std=c++17
CXX_TEST_FLAGS:=	 -mthumb -g -Wall -mcpu=$(CPU) -O2 -Werror -std=c++17
LDFLAGS = -Wl,--gc-sections,-Map=$@.map,-cref,-u,Reset_Handler -flto -ffreestanding
OBJ_COPY_OPTS:= -O ihex

TARGET:= stm32
OBJDIR := .build/obj
OBJS:= $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRC_NAMES))


HEX_TARGET:= $(TARGET).hex
ELF_TARGET:=$(TARGET).elf


FLASH:= st-flash
UPLOAD_OPT:= write 0x08000000

$(OBJDIR)/%.o : **/src/%.cpp
	mkdir -p $(OBJDIR)
	$(CXX) $(CXX_FLAGS) $(INC) -c $< -o $@
	@$(eval SOURCES_CTR=$(shell echo $$(($(SOURCES_CTR)+1))))
	@echo "[Makefile] : [$(SOURCES_CTR)/$(words $(SOURCES))] $<"

$(OBJDIR)/%.o : ./%.cpp
	mkdir -p $(OBJDIR)
	$(CXX) $(CXX_FLAGS) $(INC) -c $< -o $@
	@$(eval SOURCES_CTR=$(shell echo $$(($(SOURCES_CTR)+1))))
	@echo "[Makefile] : [$(SOURCES_CTR)/$(words $(SOURCES))] $<"
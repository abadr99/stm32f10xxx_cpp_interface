CXX:= arm-none-eabi-g++
OBJ_COPY:= arm-none-eabi-objcopy
MCU:= stm32f103c8t6
CLK:= 8000000
CPU:= cortex-m3 

CXX_FLAGS:=   	 	 -mthumb -g -Wall -mcpu=$(CPU) -O3 -Werror -std=c++17 -mcpu=cortex-m3 -mthumb   -ffunction-sections -fdata-sections -fno-exceptions  -Wall -Wextra  -DDEBUG  -DSTM32F103C8Tx -DSTM32F1  --specs=nano.specs  --specs=rdimon.specs -fno-use-cxa-atexit -DLOGGER
OPT_CXX_FLAGS:= 	 -mthumb -Wall -mcpu=$(CPU) -O3 -Werror -std=c++17 -mcpu=cortex-m3 -mthumb   -ffunction-sections -fdata-sections -fno-exceptions  -Wall -Wextra   -DSTM32F103C8Tx -DSTM32F1  --specs=nano.specs  --specs=rdimon.specs -fno-use-cxa-atexit
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

$(OBJDIR)/%.o : src/**/%.cpp
	@mkdir -p $(OBJDIR)
	@$(CXX) $(CXX_FLAGS) $(INC) -c $< -o $@
	@$(eval SOURCES_CTR=$(shell echo $$(($(SOURCES_CTR)+1))))
	@echo "[Makefile][Dev]: [$(SOURCES_CTR)/$(words $(SOURCES))] $<"

$(OBJDIR)/%.o : ./%.cpp
	@mkdir -p $(OBJDIR)
	@$(CXX) $(CXX_FLAGS) $(INC) -c $< -o $@
	@$(eval SOURCES_CTR=$(shell echo $$(($(SOURCES_CTR)+1))))
	@echo "[Makefile][Dev]: [$(SOURCES_CTR)/$(words $(SOURCES))] $<"
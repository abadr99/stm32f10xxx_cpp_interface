
CXX ?= arm-none-eabi-g++
OBJ_COPY ?= arm-none-eabi-objcopy
MCU ?= stm32f103c8t6
CLK ?= 8000000
CPU ?= cortex-m3 
LIB ?= stm32f103cpp.a

CXX_FLAGS:= -mthumb -g -Wall -mcpu=$(CPU) -O3 -Werror -std=c++17 -mcpu=cortex-m3 -mthumb -ffunction-sections -fdata-sections -fno-exceptions  -Wall -Wextra  -DDEBUG  -DSTM32F103C8Tx -DSTM32F1  --specs=nano.specs  --specs=rdimon.specs -fno-use-cxa-atexit -DLOGGER
LDFLAGS = -Wl,--gc-sections,-Map=$@.map,-cref,-u,Reset_Handler -flto -ffreestanding
OBJ_COPY_OPTS:= -O ihex
SRC = Alarm.cpp main.cpp
LIB = ./stm32f103cpp.a 
INC = -I../../dev/inc 
STARTUP_CODE = stm32f103_startup.cpp
build:
	$(CXX) $(CXX_FLAGS) $(SRC) $(STARTUP_CODE) $(LIB) $(LDFLAGS) $(INC) -T stm32f103c8t6.ld -o alarm.elf
	$(OBJ_COPY) $(OBJ_COPY_OPTS) alarm.elf alarm.hex
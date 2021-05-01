
ASM_SRC += cfg/startup_stm32f40_41xxx.s
C_SRC += lib/STM32F4xx-standard-peripherals-library/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.c
C_SRC += lib/STM32F4xx-standard-peripherals-library/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.c
C_SRC += cfg/stm32f4xx_it.c
C_SRC += cfg/system_stm32f4xx.c
C_SRC += main.c
#CPP_SRC += main.cpp

INC += -I.
INC += -Icfg
INC += -Ilib/STM32F4xx-standard-peripherals-library/Libraries/STM32F4xx_StdPeriph_Driver/inc
INC += -Ilib/STM32F4xx-standard-peripherals-library/Libraries/CMSIS/Device/ST/STM32F4xx/Include
INC += -Ilib/STM32F4xx-standard-peripherals-library/Libraries/CMSIS/Include

BUILD_DIR = build

ASM_OBJ = $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(basename $(ASM_SRC))))
C_OBJ = $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(basename $(C_SRC))))
CPP_OBJ = $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(basename $(CPP_SRC))))

OBJS += $(ASM_OBJ)
OBJS += $(C_OBJ)
OBJS += $(CPP_OBJ)

LDSCRIPT = cfg/ld/stm32f407ve.ld

CFLAGS = -c -mcpu=cortex-m4 -mthumb -mlittle-endian -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb-interwork -O0
DEFS = -DUSE_STDPERIPH_DRIVER -DSTM32F40_41xxx

# GNU ARM Embedded Toolchain
CC=arm-none-eabi-gcc
CXX=arm-none-eabi-g++
LD=arm-none-eabi-ld
AR=arm-none-eabi-ar
AS=arm-none-eabi-as
CP=arm-none-eabi-objcopy
OD=arm-none-eabi-objdump
NM=arm-none-eabi-nm
SIZE=arm-none-eabi-size
A2L=arm-none-eabi-addr2line

all: build/wheel.hex

build/wheel.hex: $(OBJS)
	arm-none-eabi-g++ -T $(LDSCRIPT) -mcpu=cortex-m4 -mthumb -mlittle-endian -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb-interwork --specs=nosys.specs -Os $(OBJS) -o build/wheel.elf
	arm-none-eabi-objcopy -O ihex build/wheel.elf build/wheel.hex
	

$(BUILD_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEFS) $(INC) $< -o $@

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEFS) $(INC) $< -o $@

$(BUILD_DIR)/%.o: %.s
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEFS) $(INC) $< -o $@

clean:
	rm -rf build

flash: build/wheel.hex
	/mnt/c/Program\ Files\ \(x86\)/STMicroelectronics/STM32\ ST-LINK\ Utility/ST-LINK\ Utility/ST-LINK_CLI.exe -c SWD -p build/wheel.hex -Rst

f: flash
.PHONY: all clean flash f

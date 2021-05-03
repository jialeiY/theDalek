PROJECT = wheel
CPP_SRC += main.cpp
CPP_SRC += utils.cpp
CPP_SRC += hw/board.cpp

ST_PHLIB = lib/STM32F4xx-standard-peripherals-library/Libraries
C_SRC += $(ST_PHLIB)/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.c
C_SRC += $(ST_PHLIB)/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.c
C_SRC += $(ST_PHLIB)/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_tim.c
C_SRC += $(ST_PHLIB)/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_exti.c
C_SRC += $(ST_PHLIB)/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_syscfg.c
C_SRC += $(ST_PHLIB)/STM32F4xx_StdPeriph_Driver/src/misc.c
C_SRC += cfg/stm32f4xx_it.c
C_SRC += cfg/system_stm32f4xx.c

ASM_SRC += cfg/startup_stm32f40_41xxx.s

LDSCRIPT = cfg/ld/stm32f407ve.ld

INC += -I.
INC += -Icfg
INC += -I$(ST_PHLIB)/STM32F4xx_StdPeriph_Driver/inc
INC += -I$(ST_PHLIB)/CMSIS/Device/ST/STM32F4xx/Include
INC += -I$(ST_PHLIB)/CMSIS/Include

BUILD_DIR = build

ASM_OBJ = $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(basename $(ASM_SRC))))
C_OBJ = $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(basename $(C_SRC))))
CPP_OBJ = $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(basename $(CPP_SRC))))

OBJS += $(ASM_OBJ)
OBJS += $(C_OBJ)
OBJS += $(CPP_OBJ)

ELF = $(BUILD_DIR)/$(PROJECT).elf
BIN = $(BUILD_DIR)/$(PROJECT).bin
HEX = $(BUILD_DIR)/$(PROJECT).hex

MCUFLAGS = -mcpu=cortex-m4 -mthumb -mlittle-endian -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb-interwork
CFLAGS = -c $(MCUFLAGS) -Os
DEFS = -DUSE_STDPERIPH_DRIVER -DSTM32F40_41xxx
LDFLAGS = $(MCUFLAGS) --specs=nosys.specs -Os

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

all: $(HEX) $(BIN)

$(HEX): $(ELF)
	$(CP) -O ihex $< $@

$(BIN): $(ELF)
	$(CP) -O binary $< $@

$(ELF): $(OBJS)
	$(CXX) -T $(LDSCRIPT) $(LDFLAGS) $^ -o $@
	
$(BUILD_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CFLAGS) -std=c++11 $(DEFS) $(INC) $< -o $@

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

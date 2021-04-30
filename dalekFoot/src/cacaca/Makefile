PROJECT = wheel
STM32_LIB=lib/STM32F4xx-standard-peripherals-library
BUILD_DIR = build

include ./cfg/setup.mk

ALLINC += -I.
ALLINC += -I$(STM32_LIB)/Libraries/CMSIS/Device/ST/STM32F4xx/Include/
ALLINC += -I$(STM32_LIB)/Libraries/CMSIS/Include/

LDFLAGS += -Wl,-Map=build/$(PROJECT).map,--cref,--no-warn-mismatch,--script=cfg/ld/stm32f407ve.ld,--gc-sections,--defsym=__process_stack_size__=0x400,--defsym=__main_stack_size__=0x400 

$(PROJECT): build/$(PROJECT).hex build/$(PROJECT).bin

ASM_SRC += cfg/startup_stm32f40_41xxx.s
C_SRC += cfg/stm32f4xx_it.c
C_SRC += cfg/system_stm32f4xx.c

CPP_SRC += main.cpp

ASM_OBJ = $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(basename $(ASM_SRC))))
C_OBJ = $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(basename $(C_SRC))))
CPP_OBJ = $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(basename $(CPP_SRC))))

$(BUILD_DIR)/%.o: %.s
	mkdir -p $(dir $@)
	$(ASM) $(ASMFLAGS) $(ALLINC) -MMD -MP -MF$(addprefix $(BUILD_DIR)/, $(addsuffix .d, $(basename $<))) -MT$@ -c $^ -o $@
	
$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(ALLINC) $^ -o $@

$(BUILD_DIR)/%.o: %.cpp
	mkdir -p build
	$(CPP) $(CPPFLAGS) $(ALLINC) $^ -o $@
	

build/$(PROJECT).elf: $(ASM_OBJ) $(C_OBJ) $(CPP_OBJ)
	$(LINKER) $(LDFLAGS) $^ -o $@

build/$(PROJECT).bin: build/$(PROJECT).elf
	arm-none-eabi-objcopy -O binary build/$(PROJECT).elf build/$(PROJECT).bin

build/$(PROJECT).hex: build/$(PROJECT).elf
	arm-none-eabi-objcopy -O ihex build/$(PROJECT).elf build/$(PROJECT).hex

flash: build/$(PROJECT).hex
	/mnt/c/Program\ Files\ \(x86\)/STMicroelectronics/STM32\ ST-LINK\ Utility/ST-LINK\ Utility/ST-LINK_CLI.exe -c SWD -p build/wheel.hex -Rst

f: flash

clean:
	rm -rf build

.PHONY: wheel clean flash f



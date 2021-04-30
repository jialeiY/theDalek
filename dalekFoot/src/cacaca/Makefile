PROJECT = wheel
STM32_LIB=lib/STM32F4xx-standard-peripherals-library

include ./cfg/setup.mk

ALLINC += -I.
ALLINC += -I$(STM32_LIB)/Libraries/CMSIS/Device/ST/STM32F4xx/Include/
ALLINC += -I$(STM32_LIB)/Libraries/CMSIS/Include/

LDFLAGS += -Wl,-Map=build/$(PROJECT).map,--cref,--no-warn-mismatch,--script=cfg/ld/stm32f407ve.ld,--gc-sections,--defsym=__process_stack_size__=0x400,--defsym=__main_stack_size__=0x400 

$(PROJECT): build/$(PROJECT).hex build/$(PROJECT).bin


build/cfg/startup_stm32f40_41xxx.o: cfg/startup_stm32f40_41xxx.s
	mkdir -p build/cfg
	$(ASM) $(ASMFLAGS) $(ALLINC) cfg/startup_stm32f40_41xxx.s -o build/cfg/startup_stm32f40_41xxx.o

build/cfg/system_stm32f4xx.o: cfg/system_stm32f4xx.c
	mkdir -p build/cfg
	$(ASM) $(CFLAGS) $(ALLINC) cfg/system_stm32f4xx.c -o build/cfg/system_stm32f4xx.o

build/main.o: main.cpp
	mkdir -p build
	$(CPP) $(CPPFLAGS) $(ALLINC) main.cpp -o build/main.o

build/$(PROJECT).elf: build/main.o build/cfg/startup_stm32f40_41xxx.o build/cfg/system_stm32f4xx.o
	$(LINKER)  build/main.o build/cfg/startup_stm32f40_41xxx.o build/cfg/system_stm32f4xx.o $(LDFLAGS) -o build/$(PROJECT).elf

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



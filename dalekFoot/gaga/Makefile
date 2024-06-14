TARGET := gaga
BUILD_DIR := build

C_SOURCES += board/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c
C_SOURCES += board/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c
C_SOURCES += board/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c.c
C_SOURCES += board/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c
C_SOURCES += board/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_adc.c
C_SOURCES += board/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c
C_SOURCES += board/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c
C_SOURCES += board/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c
C_SOURCES += board/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c
C_SOURCES += board/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc_ex.c
C_SOURCES += board/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c
C_SOURCES += board/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c_ex.c
C_SOURCES += board/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c
C_SOURCES += board/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c
C_SOURCES += board/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spi.c
C_SOURCES += board/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c
C_SOURCES += board/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c
C_SOURCES += board/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc.c
C_SOURCES += board/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c
C_SOURCES += board/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c
C_SOURCES += board/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c
C_SOURCES += board/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c
C_SOURCES += board/core/system_stm32f4xx.c
C_SOURCES += board/core/sysmem.c
C_SOURCES += board/core/stm32f4xx_hal_msp.c
C_SOURCES += board/core/stm32f4xx_it.c
C_SOURCES += board/core/syscalls.c

CPP_SOURCES += board/core/main.cpp

CPP_SOURCES += hal/serial.cpp
CPP_SOURCES += hal/gaga.cpp

ASM_SOURCES +=  board/startup/startup_stm32f407vetx.s

INCLUDES := -I./
INCLUDES += -I./board/Drivers/STM32F4xx_HAL_Driver/Inc
INCLUDES += -I./board/core
INCLUDES += -I./board/Drivers/CMSIS/Device/ST/STM32F4xx/Include
INCLUDES += -I./board/Drivers/CMSIS/Include


PREFIX := arm-none-eabi-
CC := $(PREFIX)gcc
CXX := $(PREFIX)g++
AS := $(PREFIX)gcc -x assembler-with-cpp
CP := $(PREFIX)objcopy
SZ := $(PREFIX)size
LINK := $(CXX)

HEX := $(CP) -O ihex
BIN := $(CP) -O binary -S

CPU := -mcpu=cortex-m4
FPU := -mfpu=fpv4-sp-d16
# float-abi
FLOAT-ABI = -mfloat-abi=hard
C_DEFS := -DUSE_HAL_DRIVER -DSTM32F407xx
OPT := -Os
MCU := $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

CFLAGS += -std=gnu11 $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" --specs=nano.specs
CXXFLAGS += -std=gnu++14 $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" --specs=nano.specs -fno-exceptions -fno-rtti -fno-use-cxa-atexit 



#######################################
# build the application
#######################################
# list of objects
SOURCES += $(C_SOURCES)
SOURCES += $(CPP_SOURCES)
SOURCES += $(ASM_SOURCES)
SOURCES += $(ASMM_SOURCES)

OBJECTS := $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(basename $(SOURCES))))


# all:
# 	echo $(C_SOURCES)
# 	echo $(OBJECTS)

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	mkdir -p $(dir $@)
	$(CC) "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F407xx -c $(INCLUDES) -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

$(BUILD_DIR)/%.o: %.cpp Makefile | $(BUILD_DIR)
	mkdir -p $(dir $@)
	$(CXX) "$<" -mcpu=cortex-m4 -std=gnu++14 -DUSE_HAL_DRIVER -DSTM32F407xx -c $(INCLUDES) -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(addsuffix .d,$(basename $@))" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	mkdir -p $(dir $@)
	$(AS) "$<" -mcpu=cortex-m4 -c -MMD -MP -MF"$(addsuffix .d,$(basename $@))" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

$(BUILD_DIR)/%.o: %.S Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	mkdir -p $(dir $@)
	$(LINK) -o "$@" $(OBJECTS) -mcpu=cortex-m4 -T"board/STM32F407VETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="$(addsuffix .map,$(basename $@))" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -lstdc++ -lsupc++ -Wl,--end-group
	$(SZ) $@

$(BUILD_DIR):
	mkdir $@


.PHONY: clean 
clean:
	-rm -fR $(BUILD_DIR)


.PHONY: flash
flash: $(BUILD_DIR)/$(TARGET).elf
	openocd -f /usr/share/openocd/scripts/interface/stlink.cfg -f /usr/share/openocd/scripts/target/stm32f4x.cfg -c "program $< verify reset exit"


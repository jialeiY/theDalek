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
C_SOURCES += third_party/printf/printf.c

CPP_SOURCES += board/core/main.cpp

CPP_SOURCES += hal/driver/i2c.cpp
CPP_SOURCES += hal/encoder.cpp
CPP_SOURCES += hal/gaga.cpp
CPP_SOURCES += hal/gaga_it.cpp
CPP_SOURCES += hal/motor.cpp
CPP_SOURCES += hal/serial.cpp
CPP_SOURCES += hal/spi.cpp
CPP_SOURCES += intents/common/data_pool.cpp
CPP_SOURCES += intents/common/intent_manager.cpp
CPP_SOURCES += intents/common/parameters.cpp
CPP_SOURCES += intents/debug_data_intent/debug_data_intent.cpp
CPP_SOURCES += intents/encoder_reading_intent/encoder_reading_intent.cpp
CPP_SOURCES += intents/encoder_reading_trigger_intent/encoder_reading_trigger_intent.cpp
CPP_SOURCES += intents/power_controlling_intent/power_controlling_intent.cpp
CPP_SOURCES += intents/target_maneuver_intent/target_maneuver_intent.cpp
CPP_SOURCES += intents/wheel_odometry_intent/wheel_odometry_intent.cpp
CPP_SOURCES += utils/math.cpp
CPP_SOURCES += utils/time.cpp


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


FPU := -mfpu=fpv4-sp-d16
# float-abi
FLOAT-ABI = -mfloat-abi=hard

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

CPU := -mcpu=cortex-m4
DEFINES := -DUSE_HAL_DRIVER -DSTM32F407xx
DBG := -g -O0
OPT := -Os

BUILD_OPT := $(DBG)

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	mkdir -p $(dir $@)
	$(CC) "$<" $(CPU) -std=gnu11 $(DEFINES) -c $(INCLUDES) $(BUILD_OPT) -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

$(BUILD_DIR)/%.o: %.cpp Makefile | $(BUILD_DIR)
	mkdir -p $(dir $@)
	$(CXX) "$<" $(CPU) -std=gnu++14 $(DEFINES) -c $(INCLUDES) $(BUILD_OPT) -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(addsuffix .d,$(basename $@))" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	mkdir -p $(dir $@)
	$(AS) "$<" $(CPU) -c -MMD -MP -MF"$(addsuffix .d,$(basename $@))" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	mkdir -p $(dir $@)
	$(LINK) $(BUILD_OPT) $(OBJECTS) $(CPU) -o "$@" -T"board/STM32F407VETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="$(addsuffix .map,$(basename $@))" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -lstdc++ -lsupc++ -Wl,--end-group
	$(SZ) $@

$(BUILD_DIR):
	mkdir $@


.PHONY: clean 
clean:
	-rm -fR $(BUILD_DIR)


.PHONY: flash f
flash: $(BUILD_DIR)/$(TARGET).elf
	openocd -f /usr/share/openocd/scripts/interface/stlink.cfg -f /usr/share/openocd/scripts/target/stm32f4x.cfg -c "program $< verify reset exit"



f: flash

.PHONY: debug
debug:	$(BUILD_DIR)/$(TARGET).elf flash
	openocd -f /usr/share/openocd/scripts/interface/stlink.cfg -f /usr/share/openocd/scripts/target/stm32f4x.cfg

# check the setting of a tty
#stty -F /def/ttyCH341USB0
#screen /def/ttyCH341USB0 115200
# quit screen
# Ctrl-a + \ , not Ctrl-a + Ctrl-\ 
# screen -ls
# screen -R



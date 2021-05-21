PROJECT = wheel

CPP_SRC += main.cpp
CPP_SRC += framework/thread_hub.cpp
CPP_SRC += framework/i_thread.cpp
CPP_SRC += framework/timer_thread.cpp
CPP_SRC += framework/watchdog_thread.cpp
CPP_SRC += framework/io_thread.cpp
CPP_SRC += module/sensing/mcu_decoder/mcu_usart_decoder.cpp
CPP_SRC += module/sensing/sensor_buffer/sensor_buffer.cpp

CPP_SRC += framework/entity_agency.cpp
CPP_SRC += application/dalek/dalek.cpp
CPP_SRC += hardware/wheel_sensor/wheel_sensor.cpp



C_SRC = 
ASM_SRC = 

INC += -I.

BUILD_DIR = build

ASM_OBJ = $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(basename $(ASM_SRC))))
C_OBJ = $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(basename $(C_SRC))))
CPP_OBJ = $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(basename $(CPP_SRC))))

OBJS += $(ASM_OBJ)
OBJS += $(C_OBJ)
OBJS += $(CPP_OBJ)

ELF = $(BUILD_DIR)/$(PROJECT)


CFLAGS = -c -Os -std=c++11 -g
DEFS = 
LDFLAGS = -Os -pthread -g

# GNU ARM Embedded Toolchain
CC=gcc
CXX=g++
LD=ld
AR=ar
AS=as
CP=objcopy
OD=objdump
NM=nm
SIZE=size
A2L=addr2line


all: dalek

dalek: $(ELF)

$(ELF): $(OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@
	
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

run: $(ELF)
	./$(BUILD_DIR)/$(PROJECT)

r: run

.PHONY: all clean run r

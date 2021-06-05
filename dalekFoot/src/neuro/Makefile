PROJECT = wheel

CPP_SRC += main.cpp
CPP_SRC += framework/rtdp/persistent/writer_thread.cpp
CPP_SRC += framework/rtdp/logger/logger.cpp
CPP_SRC += framework/prog/arg_parser.cpp
CPP_SRC += framework/thread/thread_hub.cpp
CPP_SRC += framework/thread/i_thread.cpp
CPP_SRC += framework/thread/loop_thread.cpp
CPP_SRC += framework/thread/control_thread.cpp
CPP_SRC += framework/thread/entity_agency.cpp
CPP_SRC += module/hardware/usart/wheel_usart.cpp
CPP_SRC += module/hardware/mcu_decoder/mcu_usart_decoder.cpp
CPP_SRC += module/mem/mem.cpp
CPP_SRC += module/time/time.cpp
CPP_SRC += application/dalek/dalek.cpp
CPP_SRC += module/sensing/i_sensor.cpp
CPP_SRC += module/sensing/wheel_sensor/wheel_sensor.cpp
CPP_SRC += action/i_action.cpp
CPP_SRC += action/power/power_action.cpp
CPP_SRC += action/odometry/odometry_action.cpp


C_SRC = 
ASM_SRC = 

INC += -I.

BUILD_DIR = build
RUNTIME_DIR = runtime

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
	mkdir -p $(RUNTIME_DIR)
	./$(BUILD_DIR)/$(PROJECT) --record-hardware-output=$(RUNTIME_DIR)/hardware.dat --record-all-output=$(RUNTIME_DIR)/hsal.dat

r: run

.PHONY: all clean run r

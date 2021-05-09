PROJECT = wheel

CPP_SRC += main.cpp
CPP_SRC += driver/serial_handler.cpp

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


CFLAGS = -c -Os -std=c++11
DEFS = 
LDFLAGS = -Os -pthread

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

all: $(ELF)

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

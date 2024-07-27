TARGET := haha
BUILD_DIR := build

C_SOURCES = 
ASM_SOURCES =

CPP_SOURCES = main.cpp
CPP_SOURCES += gen/test.pb.cc
CPP_SOURCES += intents/intent_manager.cpp
CPP_SOURCES += intents/behavior_generator/behavior_generator_intent.cpp



INCLUDES += -I./
INCLUDES += -I./third_party

PREFIX := 
CC := $(PREFIX)gcc
CXX := $(PREFIX)g++
AS := $(PREFIX)gcc -x assembler-with-cpp
CP := $(PREFIX)objcopy
SZ := $(PREFIX)size
LINK := $(CXX)

HEX := $(CP) -O ihex
BIN := $(CP) -O binary -S


CFLAGS += -std=gnu11
CXXFLAGS += -std=gnu++17

#######################################
# build the application
#######################################
# list of objects
SOURCES += $(C_SOURCES)
SOURCES += $(CPP_SOURCES)
SOURCES += $(ASM_SOURCES)
SOURCES += $(ASMM_SOURCES)

OBJECTS := $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(basename $(SOURCES))))

DEFINES := -DMCAP_IMPLEMENTATION -DMCAP_COMPRESSION_NO_LZ4 -DMCAP_COMPRESSION_NO_ZSTD
DBG := -g -O0
OPT := -Os

BUILD_OPT := $(DBG)

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	mkdir -p $(dir $@)
	$(CC) "$<" $(CFLAGS) $(DEFINES) -c $(INCLUDES) $(BUILD_OPT) -o "$@"

$(BUILD_DIR)/%.o: %.cpp Makefile | $(BUILD_DIR)
	mkdir -p $(dir $@)
	$(CXX) "$<" $(CXXFLAGS) $(DEFINES) -c $(INCLUDES) $(BUILD_OPT) -o "$@"

$(BUILD_DIR)/%.o: %.cc Makefile | $(BUILD_DIR)
	mkdir -p $(dir $@)
	$(CXX) "$<" $(CXXFLAGS) $(DEFINES) -c $(INCLUDES) $(BUILD_OPT) -o "$@"

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	mkdir -p $(dir $@)
	$(AS) "$<" -c -o "$@"

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	mkdir -p runtime
	mkdir -p $(dir $@)
	$(LINK) $(BUILD_OPT) $(OBJECTS) -lprotobuf -o "$@"
	$(SZ) $@

$(BUILD_DIR):
	mkdir $@


.PHONY: clean 
clean:
	-rm -fR $(BUILD_DIR)


.PHONY: run r
run: $(BUILD_DIR)/$(TARGET).elf
	mkdir -p runtime
	./$(BUILD_DIR)/$(TARGET).elf

r: run




TARGET := haha
BUILD_DIR := build
GEN_DIR := gen
CPP_SOURCES := 
##


C_SOURCES = 
ASM_SOURCES =

PROTO_FILES += data/proto/motion_planning_debug_topic.proto
PROTO_FILES += data/proto/odometry_topic.proto
PROTO_FILES += data/proto/planning_request_topic.proto
PROTO_FILES += data/proto/pose2d.proto
PROTO_FILES += data/proto/vector2d.proto
PROTO_FILES += data/proto/position2d.proto
PROTO_FILES += data/proto/route_topic.proto
PROTO_FILES += data/proto/polar_vector2d.proto
PROTO_FILES += data/proto/waypoint.proto

CPP_SOURCES += data/codec/odometry_topic_codec.cpp
CPP_SOURCES += data/codec/planning_request_topic_codec.cpp
CPP_SOURCES += data/codec/pose2d_codec.cpp
CPP_SOURCES += data/codec/position2d_codec.cpp
CPP_SOURCES += data/codec/route_topic_codec.cpp
CPP_SOURCES += data/codec/polar_vector2d_codec.cpp
CPP_SOURCES += intents/behavior_generator/behavior_generator_intent.cpp
CPP_SOURCES += intents/debug_writer_intent/debug_writer_intent.cpp
CPP_SOURCES += intents/intent_manager.cpp
CPP_SOURCES += intents/motion_planning_intent/motion_planning_intent.cpp
CPP_SOURCES += intents/odometry_intent/odometry_intent.cpp
CPP_SOURCES += intents/route_provision_intent/route_provision_intent.cpp
CPP_SOURCES += intents/topics/topics.cpp
CPP_SOURCES += main.cpp
CPP_SOURCES += utils/time.cpp
CPP_SOURCES += data/codec/motion_planning_debug_topic_codec.cpp
CPP_SOURCES += data/codec/waypoint_codec.cpp


INCLUDES += -I./
INCLUDES += -I./gen
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
PROTO_SOURCES := $(addprefix $(GEN_DIR)/, $(addsuffix .pb.cc, $(basename $(PROTO_FILES))))


# list of objects
SOURCES += $(C_SOURCES)
SOURCES += $(CPP_SOURCES)
SOURCES += $(ASM_SOURCES)
SOURCES += $(ASMM_SOURCES)
SOURCES += $(PROTO_SOURCES)
OBJECTS := $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(basename $(SOURCES))))

DEFINES := -DMCAP_COMPRESSION_NO_LZ4 -DMCAP_COMPRESSION_NO_ZSTD
DBG := -g -O0
OPT := -Os

BUILD_OPT := $(DBG)

$(GEN_DIR)/%.pb.cc: %.proto Makefile
	mkdir -p $(dir $@)
	protoc --cpp_out=$(GEN_DIR)/ $<

$(BUILD_DIR)/%.pb.o: %.cc | $(BUILD_DIR)
	$(CC) "$<" $(CFLAGS) $(DEFINES) -c $(INCLUDES) $(BUILD_OPT) -o "$@"

$(BUILD_DIR)/%.o: %.c Makefile $(PROTO_SOURCES) | $(BUILD_DIR)
	mkdir -p $(dir $@)
	$(CC) "$<" $(CFLAGS) $(DEFINES) -c $(INCLUDES) $(BUILD_OPT) -o "$@"

$(BUILD_DIR)/%.o: %.cpp Makefile $(PROTO_SOURCES) | $(BUILD_DIR)
	mkdir -p $(dir $@)
	$(CXX) "$<" $(CXXFLAGS) $(DEFINES) -c $(INCLUDES) $(BUILD_OPT) -o "$@"

$(BUILD_DIR)/%.o: %.cc Makefile $(PROTO_SOURCES) | $(BUILD_DIR)
	mkdir -p $(dir $@)
	$(CXX) "$<" $(CXXFLAGS) $(DEFINES) -c $(INCLUDES) $(BUILD_OPT) -o "$@"

$(BUILD_DIR)/%.o: %.s Makefile $(PROTO_SOURCES) | $(BUILD_DIR)
	mkdir -p $(dir $@)
	$(AS) "$<" -c -o "$@"

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	mkdir -p runtime
	mkdir -p $(dir $@)
	$(LINK) $(BUILD_OPT) $(OBJECTS) -lprotobuf -o "$@"
	$(SZ) $@

$(BUILD_DIR):
	mkdir $@

.PRECIOUS: $(GEN_DIR)/%.pb.cc $(GEN_DIR)/%.pb.h

.PHONY: clean 
clean:
	-rm -fR $(BUILD_DIR)
	-rm -rf $(GEN_DIR)

.PHONY: run r
run: $(BUILD_DIR)/$(TARGET).elf
	mkdir -p runtime
	./$(BUILD_DIR)/$(TARGET).elf

r: run




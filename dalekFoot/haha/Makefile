TARGET_SIL := haha-sil.elf
TARGET_HIL := haha-hil.elf
BUILD_DIR := build
GEN_DIR := gen
CPP_SOURCES := 
##


C_SOURCES = 
ASM_SOURCES =

PROTO_FILES += data/proto/behavior_topic.proto
PROTO_FILES += data/proto/ego_state_topic.proto
PROTO_FILES += data/proto/motion_planning_debug_topic.proto
PROTO_FILES += data/proto/motion_planning_topic.proto
PROTO_FILES += data/proto/odometry_topic.proto
PROTO_FILES += data/proto/passing_point.proto
PROTO_FILES += data/proto/polar_vector2d.proto
PROTO_FILES += data/proto/pose2d.proto
PROTO_FILES += data/proto/route_curvature_distribution.proto
PROTO_FILES += data/proto/route_segment.proto
PROTO_FILES += data/proto/route_topic.proto
PROTO_FILES += data/proto/trajectory_topic.proto
PROTO_FILES += data/proto/vector2d.proto
PROTO_FILES += data/proto/vehicle_request_topic.proto
PROTO_FILES += data/proto/waypoint.proto
PROTO_FILES += data/proto/system_debug_topic.proto
PROTO_FILES += data/proto/wheel_control_planning.proto
PROTO_FILES += data/proto/vehicle_response_topic.proto


CPP_SOURCES += data/codec/system_debug_codec.cpp
CPP_SOURCES += data/codec/behavior_topic_codec.cpp
CPP_SOURCES += data/codec/ego_state_topic_codec.cpp
CPP_SOURCES += data/codec/motion_planning_debug_topic_codec.cpp
CPP_SOURCES += data/codec/motion_planning_topic_codec.cpp
CPP_SOURCES += data/codec/odometry_topic_codec.cpp
CPP_SOURCES += data/codec/passing_point_codec.cpp
CPP_SOURCES += data/codec/polar_vector2d_codec.cpp
CPP_SOURCES += data/codec/pose2d_codec.cpp
CPP_SOURCES += data/codec/route_curvature_distribution_codec.cpp
CPP_SOURCES += data/codec/route_segment_codec.cpp
CPP_SOURCES += data/codec/route_topic_codec.cpp
CPP_SOURCES += data/codec/trajectory_topic_codec.cpp
CPP_SOURCES += data/codec/vector2d_codec.cpp
CPP_SOURCES += data/codec/vehicle_request_topic_codec.cpp
CPP_SOURCES += data/codec/vehicle_response_topic_codec.cpp
CPP_SOURCES += data/codec/waypoint_codec.cpp
CPP_SOURCES += data/codec/wheel_control_planning_codec.cpp
CPP_SOURCES += data/defs/vector2d.cpp
CPP_SOURCES += intents/behavior_intent/behavior_intent.cpp
CPP_SOURCES += intents/debug_writer_intent/debug_writer_intent.cpp
CPP_SOURCES += intents/debug_writer_intent/mcap_helper.cpp
CPP_SOURCES += intents/ego_state_intent/ego_state_intent.cpp
CPP_SOURCES += intents/intent_manager.cpp
CPP_SOURCES += intents/motion_planning_intent/components/frenet.cpp
CPP_SOURCES += intents/motion_planning_intent/components/profile.cpp
CPP_SOURCES += intents/motion_planning_intent/motion_planning_intent.cpp
CPP_SOURCES += intents/odometry_intent/odometry_intent.cpp
CPP_SOURCES += intents/route_intent/route_intent.cpp
CPP_SOURCES += intents/topics/topics.cpp
CPP_SOURCES += intents/trajectory_intent/trajectory/trajectory.cpp
CPP_SOURCES += intents/trajectory_intent/trajectory_intent.cpp
CPP_SOURCES += intents/vehicle_request_intent/vehicle_request_intent.cpp
CPP_SOURCES += main.cpp
CPP_SOURCES += simulator/simulator.cpp
CPP_SOURCES += utils/algo/pid.cpp
CPP_SOURCES += utils/time.cpp



INCLUDES += -I./
INCLUDES += -I./gen
INCLUDES += -I./third_party
INCLUDES += -I./../gaha_common
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
CXXFLAGS += -std=gnu++17 -Wunused-variable -Wall

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

OBJECTS_SIL := $(BUILD_DIR)/vehicle_sil.o
OBJECTS_HIL := $(BUILD_DIR)/vehicle_hil.o

DEFINES := -DMCAP_COMPRESSION_NO_LZ4 -DMCAP_COMPRESSION_NO_ZSTD
DBG := -g -O0
OPT := -Os

BUILD_OPT := $(DBG)
# BUILD_OPT := $(OPT)

all: $(BUILD_DIR)/$(TARGET_HIL) $(BUILD_DIR)/$(TARGET_SIL) 

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

$(BUILD_DIR)/$(TARGET_HIL): $(OBJECTS) $(OBJECTS_HIL) $(BUILD_DIR) Makefile
	mkdir -p runtime
	mkdir -p $(dir $@)
	$(LINK) $(BUILD_OPT) $(OBJECTS) $(OBJECTS_HIL) -lprotobuf -o "$@"
	$(SZ) $@

$(BUILD_DIR)/$(TARGET_SIL): $(OBJECTS) $(OBJECTS_SIL) $(BUILD_DIR) Makefile
	mkdir -p runtime
	mkdir -p $(dir $@)
	$(LINK) $(BUILD_OPT) $(OBJECTS) $(OBJECTS_SIL) -lprotobuf -o "$@"
	$(SZ) $@

$(BUILD_DIR):
	mkdir $@

.PRECIOUS: $(GEN_DIR)/%.pb.cc $(GEN_DIR)/%.pb.h

.PHONY: clean all
clean:
	-rm -fR $(BUILD_DIR)
	-rm -rf $(GEN_DIR)

.PHONY: run r
run: $(BUILD_DIR)/$(TARGET_SIL)
	mkdir -p runtime
	./$(BUILD_DIR)/$(TARGET_SIL)

r: run




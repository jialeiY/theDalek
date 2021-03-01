

SOURCES += src/main.cpp
SOURCES += src/utils/logger.cpp
SOURCES += src/utils/utils.cpp
SOURCES += src/sensor/ars4b.cpp
SOURCES += src/driver/spi.cpp
SOURCES += src/driver/mcp2515.cpp
SOURCES += src/driver/can.cpp

BUILD_DIR = build
TARGET = foot


CXX = g++
LD = g++



OBJECTS = $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(basename $(SOURCES))))
INCLUDES += -I.
INCLUDES += -I./src

CFLAGS = -g -O3
CXXFLAGS = -std=c++11 $(CFLAGS) $(INCLUDES)


$(BUILD_DIR)/%.o: %.cpp %.h
	mkdir -p $(dir $@)
	$(CXX) -c $(CXXFLAGS) $< -o $@


$(BUILD_DIR)/$(TARGET): $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) -o $@ -Wl,-Map=$(BUILD_DIR)/$(TARGET).map

all: $(BUILD_DIR)/$(TARGET)

.PHONY: all

run: $(BUILD_DIR)/$(TARGET)
	./build/foot
.PHONY: run

clean:
	rm -rf $(BUILD_DIR)
.PHONY: clean



SOURCES += src/main.cpp
SOURCES += src/sensor/ars4b.cpp

BUILD_DIR = build
TARGET = foot


CXX = g++
LD = g++



OBJECTS = $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(basename $(SOURCES))))
INCLUDES += -I.
INCLUDES += -I./src

CFLAGS = -g -O3
CXXFLAGS = -std=c++11 $(CFLAGS) $(INCLUDES)


$(BUILD_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) -c $(CXXFLAGS) $< -o $@


$(BUILD_DIR)/$(TARGET): $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) -o $@ -Wl,-Map=$(BUILD_DIR)/$(TARGET).map

all: $(BUILD_DIR)/$(TARGET)

.PHONY: all

run:
	./build/foot


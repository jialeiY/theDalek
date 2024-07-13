# tool macros
CC := gcc
CXX := g++
LINK := g++
CXXFLAGS := -c -I./lib/
DBGFLAGS := -g
CCOBJFLAGS := $(CXXFLAGS) -c
#LNKFLAGS := ./lib/ch341_lib.o
LNKFLAGS := -L./lib/ -lch347


# path macros
BIN_PATH := build
OBJ_PATH := build/obj
SRC_PATH := src
DBG_PATH := build/dbg

TARGET := $(BIN_PATH)/spimaster


SRC += $(SRC_PATH)/main.cpp
OBJ := $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))
OBJ_DEBUG := $(addprefix $(DBG_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))


# default rule
default: makedir all

$(TARGET): $(OBJ)
	$(LINK) $(OBJ) $(LNKFLAGS) -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	$(CC) $(CCOBJFLAGS) -o $@ $<

$(DBG_PATH)/%.o: $(SRC_PATH)/%.c
	$(CC) $(CCOBJFLAGS) $(DBGFLAGS) -o $@ $<

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(DBG_PATH)/%.o: $(SRC_PATH)/%.cpp
	$(CXX) $(CCOBJFLAGS) $(DBGFLAGS) -o $@ $<

$(TARGET_DEBUG): $(OBJ_DEBUG)
	$(CXX) $(CXXFLAGS) $(DBGFLAGS) $(OBJ_DEBUG) -o $@



.PHONY: all
all: $(TARGET)




# phony rules
.PHONY: run
run:	$(TARGET)
	./$(BIN_PATH)/spimaster

.PHONY: makedir
makedir:
	@mkdir -p $(BIN_PATH) $(OBJ_PATH) $(DBG_PATH)

.PHONY: clean
clean:
	@echo CLEAN $(CLEAN_LIST)
	@rm -f $(CLEAN_LIST)

.PHONY: test
test:
	echo $(OBJ)
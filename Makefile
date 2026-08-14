MAKEFLAGS += -r

# COMPILER = = = = = = =

CXX      := g++
CXXFLAGS := -std=c++17
CXXFLAGS += -g -O2
CXXFLAGS += -Wall -Wextra -Wpedantic
CXXFLAGS += -I./include/
CXXFLAGS += -lpthread
# CXXFLAGS += -L.

AR       := ar

INC_DIR := include
LIB_DIR := lib
OUT_DIR := outputs

LIB_SRCS := src/stream/PNMStream.cpp \
            src/stream/buffer/PPMBuffer.cpp \
            src/stream/buffer/PGMBuffer.cpp \
            src/stream/buffer/PBMBuffer.cpp

LIB_OBJS := $(patsubst src/%.cpp,$(OUT_DIR)/%.o,$(LIB_SRCS))
LIB_STATIC := $(LIB_DIR)/libpnmstream.a

DEMO_SRCS := examples/demo.cpp
DEMO_OBJS := $(OUT_DIR)/examples/demo.o
DEMO_BIN  := $(OUT_DIR)/pnmstream_demo


# TOOLS = = = = = = = = = =

.PHONY: all clean test lib demo

all: lib demo

$(LIB_DIR):
	@mkdir -p $@

$(OUT_DIR)/stream/PNMStream.o: src/stream/PNMStream.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

$(OUT_DIR)/stream/buffer/PPMBuffer.o: src/stream/buffer/PPMBuffer.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

$(OUT_DIR)/stream/buffer/PGMBuffer.o: src/stream/buffer/PGMBuffer.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

$(OUT_DIR)/stream/buffer/PBMBuffer.o: src/stream/buffer/PBMBuffer.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

$(LIB_STATIC): $(LIB_OBJS)
	@mkdir -p $(LIB_DIR)
	$(AR) rcs $@ $(LIB_OBJS)

lib: $(LIB_STATIC)

$(OUT_DIR)/examples/demo.o: examples/demo.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

$(DEMO_BIN): $(LIB_STATIC) $(DEMO_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(DEMO_OBJS) -L$(LIB_DIR) -lpnmstream

demo: $(DEMO_BIN)

test:
	+$(MAKE) -C tests test

clean:
	rm -rf $(OUT_DIR) $(LIB_DIR)
	+$(MAKE) -C tests clean


CXX      = g++
CXXFLAGS = -Wall -Wextra -g -std=c++17
AR       = ar
ARFLAGS  = rcs

SRC_DIR      = src
INCLUDE_DIR  = include
LIB_DIR      = lib

INCLUDES = -I$(INCLUDE_DIR) -I$(INCLUDE_DIR)/ppmstream

LIB_SRCS = $(SRC_DIR)/stream/PPMBuffer.cpp \
            $(SRC_DIR)/stream/PPMDrawer.cpp \
            $(SRC_DIR)/stream/PPMStream.cpp

LIB_OBJS = $(LIB_SRCS:.cpp=.o)

DEPS = $(LIB_OBJS:.o=.d)

LIB_TARGET = $(LIB_DIR)/libppmstream.a

# = = = = = = =

.PHONY:
	all
	library
	clean
	clean-outputs
	clean-output-frames
	clean-output-video

all: library

library: $(LIB_TARGET)

$(LIB_TARGET): $(LIB_OBJS) | $(LIB_DIR)
	$(AR) $(ARFLAGS) $@ $^

$(SRC_DIR)/stream/%.o: $(SRC_DIR)/stream/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

$(LIB_DIR):
	mkdir -p $@

-include $(DEPS)

clean:
	rm -rf $(LIB_DIR)
	rm -f $(SRC_DIR)/stream/*.o $(SRC_DIR)/stream/*.d

# 输出目录
OUTPUTS = ./outputs

clean-outputs: clean-output-frames clean-output-video

clean-output-frames:
	rm $(OUTPUTS)/output-frames/*

clean-output-video:
	rm $(OUTPUTS)/output-video/*


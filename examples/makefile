CXX = g++
CXXSTD = -std=c++17
CXXFLAGS = -Wall -Wextra -g $(CXXSTD)

INCLUDE_DIR = ../include
SRC_DIR = ../src/stream

SRCS = $(SRC_DIR)/*.cpp demo.cpp
INCLUDES = $(INCLUDE_DIR)/ppmstream.hpp
# INCLUDES = -I$(INCLUDE_DIR) -I$(INCLUDE_DIR)/ppmstream

demo: $(INCLUDES) $(SRCS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# = = = = = = =

.PHONY:
	clean

clean:
	rm demo


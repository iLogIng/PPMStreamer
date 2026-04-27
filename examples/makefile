CXX = g++
CXXSTD = -std=c++17
CXXFLAGS = -Wall -Wextra -g $(CXXSTD)

INCLUDE_DIR = ../include
SRC_DIR = ../src/stream

SRCS = $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/buffer/*.cpp)

demo: demo.cpp $(SRCS)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) $^ -o $@

.PHONY: clean

clean:
	rm -f demo

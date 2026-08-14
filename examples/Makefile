CXX := g++
CXXFLAGS := -std=c++17
CXXFLAGS += -g -O2
CXXFLAGS += -Wall -Wextra
CXXFLAGS += -I../include/
CXXFLAGS += -L../lib/
CXXFLAGS += -lpthread \
			-lpnmstream

INC_DIR := ../include
SRC_DIR := ../src/stream

SRCS := $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/buffer/*.cpp)

demo: demo.cpp $(SRCS)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) $^ -o $@

.PHONY: clean

clean:
	rm -f demo



CXX = g++
CXX_FLAGES = -Wall -g

SRC_PATH = ./src

INCLUDE_PATH = include
INCLUDE_SUBDIRS = math stream utils

INCLUDES = -I$(INCLUDE_PATH) $(addprefix -I$(INCLUDE_PATH)/, $(INCLUDE_SUBDIRS))

HEADERS = $(wildcard $(INCLUDE_PATH)/*/*.hpp)

SOURCE = main.cpp

TARGET = main

# = = = = = =

outprint:
	@echo $(INCLUDES)

$(TARGET): $(SOURCE) $(HEADERS)
	$(CXX) $(CXX_FLAGES) $(INCLUDES) $< -o $@

.PHONY:
	clean

clean:
	rm $(TARGET)

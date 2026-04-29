CXX      := g++
CXXSTD   := -std=c++17
CXXFLAGS := $(CXXSTD) -g -Wall -Wextra -Wpedantic

INC_DIR  := ../include
OUT_DIR  := outputs

GTEST_LIBS := -lgtest -lgtest_main -lpthread

LIB_SRCS := ../src/stream/PNMStream.cpp \
            ../src/stream/buffer/PPMBuffer.cpp \
            ../src/stream/buffer/PGMBuffer.cpp \
            ../src/stream/buffer/PBMBuffer.cpp

LIB_OBJS := $(OUT_DIR)/stream/PNMStream.o \
            $(OUT_DIR)/stream/buffer/PPMBuffer.o \
            $(OUT_DIR)/stream/buffer/PGMBuffer.o \
            $(OUT_DIR)/stream/buffer/PBMBuffer.o

TEST_SRCS := test_Math.cpp test_Pixel.cpp test_PNMStream.cpp
TEST_OBJS := $(addprefix $(OUT_DIR)/,$(TEST_SRCS:.cpp=.o))
TEST_BIN  := $(OUT_DIR)/test_pnmstream

.PHONY: all clean test

all: $(TEST_BIN)

# Generic rule: compile any .cpp to .o under outputs/
$(OUT_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

$(OUT_DIR)/%.o: ../src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

$(TEST_BIN): $(LIB_OBJS) $(TEST_OBJS)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(GTEST_LIBS)

test: $(TEST_BIN)
	./$(TEST_BIN)

clean:
	rm -rf $(OUT_DIR)

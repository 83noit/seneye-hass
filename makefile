CXX := g++
FLAGS= -std=c++14 -Wall -Wextra

SOURCE_DIR := src
BUILD_DIR := build
TEST_DIR := test
TEST_BUILD_DIR := $(BUILD_DIR)/$(TEST_DIR)
BINARY_DIR := bin

HEADERS := -I src
LDLIBS := -lhidapi-libusb -lmosquittopp

BINARY := seneye
TEST_BINARY := test_$(BINARY)

SOURCES := $(wildcard $(SOURCE_DIR)/*.cpp)
OBJECTS := $(patsubst $(SOURCE_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCES))

TEST_SOURCES := $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJECTS := $(patsubst $(TEST_DIR)/%.cpp, $(TEST_BUILD_DIR)/%.o, $(TEST_SOURCES))

.PHONY: clean format test

all: $(BUILD_DIR) $(BINARY_DIR) $(BINARY_DIR)/$(BINARY)

debug: FLAGS += -g
debug: $(BUILD_DIR) $(BINARY_DIR) $(BINARY_DIR)/$(BINARY)

$(BINARY_DIR)/$(BINARY): $(OBJECTS)
	$(CXX) $(FLAGS) $(LDLIBS) -o $@ $^

$(BUILD_DIR)/%.o : $(SOURCE_DIR)/%.cpp
	$(CXX) $(FLAGS) $(HEADERS) -o $@ -c $<

test: $(TEST_BUILD_DIR) $(BINARY_DIR) $(BINARY_DIR)/$(TEST_BINARY)
	./$(BINARY_DIR)/$(TEST_BINARY)

$(BINARY_DIR)/$(TEST_BINARY): $(TEST_BUILD_DIR)/catch_amalgamated.o $(TEST_OBJECTS) $(BUILD_DIR)/seneye.o $(BUILD_DIR)/sud.o
	$(CXX) $(FLAGS) $(LDLIBS) -o $@ $^

$(TEST_BUILD_DIR)/catch_amalgamated.o: $(TEST_DIR)/catch_amalgamated.cpp
	$(CXX) -Wno-psabi $(HEADERS) -o $@ -c $<

$(TEST_DIR)/catch_amalgamated.cpp:
	curl -s -S -L -f https://raw.githubusercontent.com/catchorg/Catch2/devel/extras/catch_amalgamated.hpp -z $(TEST_DIR)/catch_amalgamated.hpp -o $(TEST_DIR)/catch_amalgamated.hpp
	curl -s -S -L -f https://raw.githubusercontent.com/catchorg/Catch2/devel/extras/catch_amalgamated.cpp -z $@ -o catch_amalgamated.cpp.tmp && mv -f catch_amalgamated.cpp.tmp $@ 2>/dev/null || rm -f catch_amalgamated.cpp.tmp $@

$(TEST_BUILD_DIR)/%.o : $(TEST_DIR)/%.cpp
	$(CXX) $(FLAGS) $(HEADERS) -o $@ -c $<

$(BINARY_DIR):
	mkdir -p $(BINARY_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TEST_BUILD_DIR):
	mkdir -p $(TEST_BUILD_DIR)

clean:
	rm -f $(BINARY_DIR)/$(BINARY) $(BINARY_DIR)/$(TEST_BINARY) $(OBJECTS) $(TEST_OBJECTS)

format: SHELL := /bin/zsh
format:
	clang-format -i {$(SOURCE_DIR),$(TEST_DIR)}/**/*{.cpp,.h}(N)

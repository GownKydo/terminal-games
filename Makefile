# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Iheaders -std=c++17

# Directories
SRC_DIR = src
BUILD_DIR = build
OBJ_DIRS = $(BUILD_DIR)/run.o $(BUILD_DIR)/src/hangman/main.o $(BUILD_DIR)/src/hangman/socket/server.o $(BUILD_DIR)/src/hangman/socket/client.o $(BUILD_DIR)/src/buscaminas/main.o $(BUILD_DIR)/src/snake/main.o

# Output binary
TARGET = game

# Source files
SRCS = run.cpp \
       src/hangman/main.cpp \
       src/hangman/socket/server.cpp \
       src/hangman/socket/client.cpp \
       src/buscaminas/main.cpp \
       src/snake/main.cpp

# Object files
OBJS = build/run.o \
       build/src/hangman/main.o \
       build/src/hangman/socket/server.o \
       build/src/hangman/socket/client.o \
       build/src/buscaminas/main.o \
       build/src/snake/main.o

# Default target
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

# Compile source files into object files
build/run.o: run.cpp
	mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/src/hangman/main.o: src/hangman/main.cpp
	mkdir -p build/src/hangman
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile Socket-related files
$(BUILD_DIR)/src/hangman/socket/%o: src/hangman/socket/%cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/src/buscaminas/main.o: src/buscaminas/main.cpp
	mkdir -p build/src/buscaminas
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/src/snake/main.o: src/snake/main.cpp
	mkdir -p build/src/snake
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target
clean:
	rm -rf build $(TARGET)

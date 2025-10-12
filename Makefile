# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Iheaders

# Directories
SRC_DIR = src
BUILD_DIR = build
OBJ_DIRS = $(BUILD_DIR)/run.o $(BUILD_DIR)/src/hangman/main.o $(BUILD_DIR)/src/nuscaminas/main.o

# Output binary
TARGET = game

# Source files
SRCS = run.cpp \
       src/hangman/main.cpp \
       src/nuscaminas/main.cpp

# Object files
OBJS = build/run.o \
       build/src/hangman/main.o \
       build/src/nuscaminas/main.o

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

build/src/nuscaminas/main.o: src/nuscaminas/main.cpp
	mkdir -p build/src/nuscaminas
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target
clean:
	rm -rf build $(TARGET)

# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Iheaders -std=c++17
LDFLAGS = -lncurses

# Directories
SRC_DIR = src
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/run.o $(BUILD_DIR)/src/hangman/main.o $(BUILD_DIR)/src/hangman/socket/server.o $(BUILD_DIR)/src/hangman/socket/client.o $(BUILD_DIR)/src/buscaminas/main.o $(BUILD_DIR)/src/snake/main.o

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
OBJS = $(SRCS:%.cpp=$(BUILD_DIR)/%.o)

# Default target
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile source files into object files
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)  # Make sure the directory exists before compilation
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target
clean:
	rm -rf build $(TARGET)

.PHONY: clean all

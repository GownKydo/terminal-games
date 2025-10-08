# Makefile para compilar el proyecto

CXX = g++
CXXFLAGS = -Iheaders -Wall
BUILD_DIR = build
SRC_DIR = src
EXEC = game

# Archivos fuente
SRC = $(SRC_DIR)/hangman/main.cpp $(SRC_DIR)/nuscaminas/main.cpp run.cpp

# Archivos objeto (con las rutas completas para cada archivo fuente)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Regla para preparar los directorios
prepare:
	mkdir -p $(BUILD_DIR)/src/hangman
	mkdir -p $(BUILD_DIR)/src/nuscaminas

# Regla para compilar
all: prepare $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(OBJ) -o $(EXEC)

# Regla para compilar los archivos .cpp a .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# Limpiar los archivos generados
clean:
	rm -rf $(BUILD_DIR)/*.o $(EXEC)

.PHONY: all clean prepare

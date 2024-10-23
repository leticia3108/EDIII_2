CC = gcc
CFLAGS = -g -Wall -O0 -std=c99
INCLUDE = $(wildcard include/*.h)
SOURCES = $(wildcard src/*.c)
OBJ = $(SOURCES:$(SRC_DIR)/%.c = $(BUILD_DIR)/%.o)
# INCLUDE_OBJ = $(INCLUDE:src/%.c=src/%.o)
TARGET = $(BIN_DIR)/executavel

# Diretórios
SRC_DIR = src
BIN_DIR = bin
INC_DIR = include
BUILD_DIR = build

# Criar diretórios bin e build
$(BIN_DIR):
	mkdir -p $(BIN_DIR)
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compilar arquivos .c em arquivos .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/%.h $(INC_DIR)/main.h
	$(CC) $(CFLAGS) -c $< -o $@

all: $(OBJ) $(BUILD_DIR) $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

run: $(TARGET)
	$(TARGET)

.PHONY: clean

clean:
	@rm -f $(BUILD_DIR)/*.o $(TARGET) core

zip: 
	@rm -f *.zip
	zip -r edIII.zip $(INC_DIR)/* $(SRC_DIR)/* ./Makefile

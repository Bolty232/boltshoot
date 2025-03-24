CC = g++
CFLAGS = -Wall -Wextra
INCLUDES = -I./include
LIBS = -lglfw -lGL -lGLEW -lGLU -lSDL2main -lSDL2

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

TARGET = $(BIN_DIR)/boltshoot

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

all: directories $(TARGET)

directories:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(TARGET): $(OBJ_FILES)
	$(CC) $^ -o $@ $(LIBS)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

run: all
	$(TARGET)

.PHONY: all clean run directories

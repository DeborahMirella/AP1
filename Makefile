
CC = gcc
CFLAGS = -Wall -g
INCLUDES = -Iinclude

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INCLUDE_DIR = include

OBJ = $(OBJ_DIR)/mat.o $(OBJ_DIR)/matop.o
TARGET = $(BIN_DIR)/matop

all: $(TARGET)

$(TARGET): $(OBJ)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

$(OBJ_DIR)/mat.o: $(SRC_DIR)/mat.c $(INCLUDE_DIR)/mat.h $(INCLUDE_DIR)/msgassert.h
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRC_DIR)/mat.c -o $@

$(OBJ_DIR)/matop.o: $(SRC_DIR)/matop.c $(INCLUDE_DIR)/mat.h $(INCLUDE_DIR)/msgassert.h
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRC_DIR)/matop.c -o $@

run: $(TARGET)
	./$(TARGET) -s -x 5 -y 5
	./$(TARGET) -m -x 5 -y 5
	./$(TARGET) -t -x 5 -y 5

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)



CC = gcc
CFLAGS = -g -Wall -O0 -std=c99
SOURCES = $(wildcard src/*.c)
OBJS = $(SOURCES:src/%.c=src/%.o)
TARGET = main

# COmpilar arquivos .o em arquivos .c
%.o: %.c src/header.h
	$(CC) $(CFLAGS) -c $< -o $@

# Linkar os objetos
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

all: $(TARGET)

.PHONY: clean

clean:
	@rm -f src/*.o $(TARGET) core

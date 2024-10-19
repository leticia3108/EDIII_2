
CC = gcc
CFLAGS = -g -Wall -O0 -std=c99
SOURCES = $(wildcard src/*.c)
OBJS = $(SOURCES:src/%.c=src/%.o)
TARGET = main

# Compilar arquivos .o em arquivos .c
%.o: %.c src/header.h
	$(CC) $(CFLAGS) -c $< -o $@

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

run: 
	./main

.PHONY: clean

clean:
	@rm -f src/*.o $(TARGET) core

zip: 
	zip -r edIII.zip src/ Makefile

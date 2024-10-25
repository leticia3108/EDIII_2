
CC = gcc
CFLAGS = -g -Wall -O0 -std=c99
INCLUDE = $(wildcard include/*.c)
SOURCES = $(wildcard src/*.c)
OBJS = $(SOURCES:include/%.c=include/%.o)
INCLUDE_OBJS = $(INCLUDE:src/%.c=src/%.o)
TARGET = main

# Compilar arquivos .c em arquivos .o
%.o: %.c src/header.h include/funcoes_fornecidas.h
	$(CC) $(CFLAGS) -c $< -o $@

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDE_OBJS) -o $(TARGET)

run: 
	./main

.PHONY: clean

clean:
	@rm -f src/*.o $(TARGET) core

zip: 
	zip -r edIII.zip src/ include/ Makefile

# Variables
CC = g++
CFLAGS = 

# Flags for Debug and Optimization modes
DEBUG_FLAGS = -g -O0 -Wall
OPTIM_FLAGS = -O2

# Target to compile in Optimization mode
opt: CFLAGS += $(OPTIM_FLAGS)
opt: all

# Target to compile in Debug mode
dbg: CFLAGS += $(DEBUG_FLAGS)
dbg: all

# Rule for compiling the program
all: mps

mps: bin/main.o
	$(CC) $(CFLAGS) -o bin/mps main.o

# Rules for object files
bin/main.o: src/main.cpp
	$(CC) $(CFLAGS) -c src/main.cpp -o main.o

# Clean up build files
clean:
	rm -f ./bin/*

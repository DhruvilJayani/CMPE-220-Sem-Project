# Simple Makefile for your Software CPU project

# Compiler
CC = gcc

# Compiler flags: -Wall (show warnings) -Wextra (more warnings) -g (debug info)
CFLAGS = -Wall -Wextra -g

# All C source files
SRC = cpu.c alu.c memory.c program_layout.c bus.c io.c control_unit.c encoder.c compiler.c main.c

# Output executable name
OUT = cpu_sim

# Default target: build everything
all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) -o $(OUT) $(SRC)

# Run the emulator
run: $(OUT)
	./$(OUT)

# Clean up compiled files
clean:
	rm -f $(OUT)

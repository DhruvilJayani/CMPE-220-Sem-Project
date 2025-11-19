#ifndef COMPILER_H
#define COMPILER_H

#include <stdint.h>
#include "cpu.h"   // ✅ So CPU is defined here

// -------------------------------------------------------------
// Simple Assembler / Compiler front-end
// Connects encoder + emulator
// -------------------------------------------------------------

// Converts an assembly (.asm) file to a binary (.txt)
void assemble_program(const char *asm_file, const char *bin_file);

// Loads a binary file into CPU memory (text segment)
void load_binary_into_cpu(CPU *cpu, const char *bin_file);

#endif

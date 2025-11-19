#ifndef BUS_H
#define BUS_H

#include <stdint.h>
#include "cpu.h"           // ✅ Now the compiler knows what CPU is
#include "memory.h"
#include "program_layout.h"
#include "io.h"

// -------------------------------------------------------------
// Unified memory bus definitions
// -------------------------------------------------------------
// These constants match your memory layout.
#define TEXT_START   0x0000
#define TEXT_END     0x1FFF
#define DATA_START   0x2000
#define DATA_END     0x3FFF
#define HEAP_START   0x4000
#define HEAP_END     0x4FFF
#define STACK_BASE   0xF000     // renamed to avoid duplicate macro
#define STACK_END    0xFFFF
#define MMIO_START   0x8000
#define MMIO_END     0x8FFF

// -------------------------------------------------------------
// Function declarations for memory bus
// -------------------------------------------------------------

// Fetch 16-bit instruction from text segment
uint16_t bus_fetch16(CPU *cpu, uint16_t pc);

// Generic 16-bit read (used by ALU or CPU)
uint16_t bus_read16(CPU *cpu, uint16_t addr);

// Generic 16-bit write (used by ALU or CPU)
void bus_write16(CPU *cpu, uint16_t addr, uint16_t value);

#endif

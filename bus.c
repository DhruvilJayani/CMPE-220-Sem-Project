#include "bus.h"
#include <stdio.h>

// -------------------------------------------------------------
// FETCH - read instruction from the text (program) segment
// -------------------------------------------------------------
uint16_t bus_fetch16(CPU *cpu, uint16_t pc) {
    if (pc < TEXT_END)
        return cpu->segments->text_segment[pc];
    else {
        printf("[BUS] Invalid PC fetch: 0x%04X\n", pc);
        return 0;
    }
}

// -------------------------------------------------------------
// READ - read a 16-bit word from unified memory space
// -------------------------------------------------------------
uint16_t bus_read16(CPU *cpu, uint16_t addr) {
    if (addr >= TEXT_START && addr <= TEXT_END)
        return cpu->segments->text_segment[addr - TEXT_START];
    else if (addr >= DATA_START && addr <= DATA_END)
        return cpu->segments->data_segment[addr - DATA_START];
    else if (addr >= HEAP_START && addr <= HEAP_END)
        return cpu->segments->heap_segment[addr - HEAP_START];
    else if (addr >= STACK_BASE && addr <= STACK_END)
        return cpu->segments->stack_segment[addr - STACK_BASE];
    else if (addr >= MMIO_START && addr <= MMIO_END)
        return io_read(addr);
    else {
        printf("[BUS] Invalid memory read: 0x%04X\n", addr);
        return 0;
    }
}

// -------------------------------------------------------------
// WRITE - write a 16-bit word to unified memory or I/O space
// -------------------------------------------------------------
void bus_write16(CPU *cpu, uint16_t addr, uint16_t value) {
    if (addr >= DATA_START && addr <= DATA_END)
        cpu->segments->data_segment[addr - DATA_START] = value;
    else if (addr >= HEAP_START && addr <= HEAP_END)
        cpu->segments->heap_segment[addr - HEAP_START] = value;
    else if (addr >= STACK_BASE && addr <= STACK_END)
        cpu->segments->stack_segment[addr - STACK_BASE] = value;
    else if (addr >= MMIO_START && addr <= MMIO_END)
        io_write(addr, value);
    else {
        printf("[BUS] Invalid memory write: 0x%04X\n", addr);
    }
}

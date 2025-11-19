#ifndef IO_H
#define IO_H

#include <stdint.h>

// MMIO base address mapping
#define UART_ADDR   0x8000   // Console output
#define TIMER_ADDR  0x8002   // Simple timer counter

// Initialize I/O devices
void io_init(void);

// I/O access functions (used by bus.c)
uint16_t io_read(uint16_t addr);
void io_write(uint16_t addr, uint16_t value);

// Timer tick (simulate one CPU cycle)
void io_timer_tick(void);

// Utility for "Hello, World" or program output
void io_flush_output(void);

#endif

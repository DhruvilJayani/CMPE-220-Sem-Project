#include "io.h"
#include <stdio.h>

static uint16_t timer_counter = 0;
static char uart_buffer[256];
static int uart_index = 0;

void io_init(void) {
    timer_counter = 0;
    uart_index = 0;
}

uint16_t io_read(uint16_t addr) {
    if (addr == TIMER_ADDR) {
        return timer_counter;
    }
    // UART read not needed (write-only device)
    return 0;
}

void io_write(uint16_t addr, uint16_t value) {
    if (addr == UART_ADDR) {
        // Store characters until newline or flush
        char c = (char)(value & 0xFF);
        if (uart_index < 255) {
            uart_buffer[uart_index++] = c;
            if (c == '\n' || uart_index >= 255)
                io_flush_output();
        }
    } 
    else if (addr == TIMER_ADDR) {
        // Writing resets timer
        timer_counter = 0;
    }
}

void io_timer_tick(void) {
    // Called once per instruction to simulate timer increment
    timer_counter++;
}

void io_flush_output(void) {
    uart_buffer[uart_index] = '\0';
    printf("[UART OUTPUT]: %s", uart_buffer);
    uart_index = 0;
}

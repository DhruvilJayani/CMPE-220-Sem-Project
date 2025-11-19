
/* memory_and_registers.h */

#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

/* Define the size of memory */
#define MEMORY_SIZE 65536  // 64KB
#define MEMORY_START 0x0000

/* Additional definitions for easy access */
#define TOTAL_REGISTERS 8

typedef struct{
    uint32_t GPR[TOTAL_REGISTERS];
    uint32_t SPR[TOTAL_REGISTERS];
} regs;

/* General Purpose register address */
#define R0 0x0000
#define R1 0x0004
#define R2 0x0008
#define R3 0x000C
#define R4 0x0010
#define R5 0x0014
#define R6 0x0018
#define R7 0x001C

/* Special purpose register address */
#define RA 0x0004
#define SP 0x0024
#define PC 0x0028

/* Function prototypes */
void initialize_memory(void);
void initialize_registers(regs *REG);

#endif /* MEMORY_AND_REGISTERS_H */
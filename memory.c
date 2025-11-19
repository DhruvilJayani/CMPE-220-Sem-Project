
/* Implementation file memory_and_registers.c */

#include "memory.h"
#include <string.h> // For memset


/* Memory declaration */
uint8_t memory[MEMORY_SIZE];

/* Initialize memory to zero */
void initialize_memory(void) {
    memset(memory, 0, MEMORY_SIZE);
}

/* Initialize registers to zero */
void initialize_registers(regs *REG) {
    for (int i = 0; i < TOTAL_REGISTERS; i++) {
        REG->GPR[i] = 0;
        REG->SPR[i] = 0;
    }
}
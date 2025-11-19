#ifndef ALU_H
#define ALU_H

#include <stdint.h>
#include "cpu.h"

// execute returns 1 if PC was changed (branch/jump)
// 0 means PC should auto-increment normally
int execute(CPU *cpu, uint8_t opcode, uint8_t addr_mode, uint8_t dest, uint8_t src);

#endif

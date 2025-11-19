#ifndef CONTROL_UNIT_H
#define CONTROL_UNIT_H

#include <stdint.h>
#include "cpu.h"
#include "bus.h"
#include "alu.h"
#include "io.h"

// Start execution of the loaded program.
// NOTE: Use CPU* (not struct CPU*) because CPU is a typedef in cpu.h.
void run_cpu(CPU *cpu);

#endif

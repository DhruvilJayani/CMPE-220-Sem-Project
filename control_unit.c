#include "control_unit.h"
#include <stdio.h>

// ------------------------------------------------------------
// Main Control Loop
// ------------------------------------------------------------
void run_cpu(CPU *cpu) {

    printf("\n=== CPU START ===\n");

    while (1) {
        uint16_t instr = bus_fetch16(cpu, cpu->pc);
        uint8_t addr_mode = (instr >> 15) & 0x1;
        uint8_t opcode    = (instr >> 10) & 0x1F;
        uint8_t dest      = (instr >>  5) & 0x1F;
        uint8_t src       =  instr        & 0x1F;

        printf("\n[Cycle] PC=%04X OPCODE=%02u DEST=%02u SRC=%02u MODE=%u\n",
               cpu->pc, opcode, dest, src, addr_mode);

        int pc_changed = execute(cpu, opcode, addr_mode, dest, src);

        if (cpu->flags & FLAG_HALT)
            break;

        if (!pc_changed)
            cpu->pc++;

        io_timer_tick();
    }

    // ------------------------------------------------------
    // Universal report after HALT
    // ------------------------------------------------------
    printf("\n=== CPU HALTED ===\n");
    printf("=== Register Dump ===\n");
    for (int i = 0; i < 8; i++)
        printf("R%d = %d\n", i, cpu->Register->GPR[i]);

    printf("\n=== Memory Dump (first 32 words) ===\n");
    for (int i = 0; i < 32; i++)
        printf("DATA[%02d] = %d\n", i, cpu->memory[i]);

    io_flush_output();
    printf("\n=== END OF PROGRAM ===\n");
}

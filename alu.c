#include "alu.h"
#include <stdio.h>

// ------------------------------------------------------------
// ALU & Execution Logic
// ------------------------------------------------------------

int execute(CPU *cpu, uint8_t opcode, uint8_t addr_mode, uint8_t dest, uint8_t src) {

    printf("\nExecuting: OPCODE=%d MODE=%d DEST=R%d SRC=%d\n", opcode, addr_mode, dest, src);

    switch (opcode) {

        // ---------------- HALT ----------------
        case HALT:
            printf("Inside HALT\n");
            cpu->flags |= FLAG_HALT;
            return 1; // Stop execution

        // ---------------- MOV ----------------
        case MOV:
            if (addr_mode == 0)
                cpu->Register->GPR[dest] = cpu->Register->GPR[src];
            else
                cpu->Register->GPR[dest] = src;
            printf("MOV -> R%d = %d\n", dest, cpu->Register->GPR[dest]);
            return 0;

        // ---------------- ADD ----------------
        case ADD:
            if (addr_mode == 0)
                cpu->Register->GPR[dest] += cpu->Register->GPR[src];
            else
                cpu->Register->GPR[dest] += src;
            printf("ADD -> R%d = %d\n", dest, cpu->Register->GPR[dest]);
            return 0;

        // ---------------- SUB ----------------
        case SUB:
            if (addr_mode == 0)
                cpu->Register->GPR[dest] -= cpu->Register->GPR[src];
            else
                cpu->Register->GPR[dest] -= src;
            printf("SUB -> R%d = %d\n", dest, cpu->Register->GPR[dest]);
            return 0;

        // ---------------- MUL ----------------
        case MUL:
            if (addr_mode == 0)
                cpu->Register->GPR[dest] *= cpu->Register->GPR[src];
            else
                cpu->Register->GPR[dest] *= src;
            printf("MUL -> R%d = %d\n", dest, cpu->Register->GPR[dest]);
            return 0;

        // ---------------- LD ----------------
        case LD: {
            printf("Inside LD\n");
            if (addr_mode == 0) {
                // Load from address stored in source register
                uint16_t addr = cpu->Register->GPR[src];
                if (addr < MEMORY_SIZE) {
                    cpu->Register->GPR[dest] = cpu->memory[addr];
                    printf("LD -> R%d = memory[%d] (%d)\n",
                           dest, addr, cpu->Register->GPR[dest]);
                } else {
                    printf("LD ERROR: Invalid address %d\n", addr);
                }
            } else {
                // Immediate load
                cpu->Register->GPR[dest] = src;
                printf("LD immediate -> R%d = %d\n", dest, src);
            }
            return 0;
        }

        // ---------------- SW ----------------
        case SW: {
            printf("Inside SW\n");
            uint16_t addr = cpu->Register->GPR[src]; // use value in src as address
            if (addr < MEMORY_SIZE) {
                cpu->memory[addr] = cpu->Register->GPR[dest];
                printf("SW -> memory[%d] = R%d (%d)\n",
                       addr, dest, cpu->Register->GPR[dest]);
            } else {
                printf("SW ERROR: Invalid address %d\n", addr);
            }
            return 0;
        }

        // --------------------------------------------------------
        // CMP - Compare register or immediate, set FLAG_LE
        // --------------------------------------------------------
        case CMP: {
            int16_t left  = cpu->Register->GPR[dest];
            int16_t right = (addr_mode == 0) ? cpu->Register->GPR[src] : src;

            cpu->flags &= ~FLAG_LE; // clear previous flag
            if (left <= right)
                cpu->flags |= FLAG_LE;

            printf("CMP %d <= %d -> FLAG_LE=%d\n",
                   left, right, (cpu->flags & FLAG_LE) ? 1 : 0);
            return 0;
        }

        // --------------------------------------------------------
        // BLE - Branch if Less or Equal
        // --------------------------------------------------------
        case BLE:
            if (cpu->flags & FLAG_LE) {
                cpu->pc = dest;
                printf("BLE taken -> jump to %d\n", dest);
                return 1; // PC handled
            } else {
                printf("BLE not taken\n");
                return 0;
            }

        // ---------------- J ----------------
        case J:
            cpu->pc = dest;
            printf("JUMP -> PC=%d\n", cpu->pc);
            return 1; // PC changed

        default:
            printf("Unknown opcode %d\n", opcode);
            return 0;
    }
}

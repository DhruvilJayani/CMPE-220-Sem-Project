#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpu.h"
#include "compiler.h"
#include "control_unit.h"
#include "program_layout.h"
#include "memory.h"
#include "io.h"

// -------------------------------------------------------------
// MAIN FUNCTION - Entry point for your software CPU
// -------------------------------------------------------------
int main(int argc, char *argv[]) {

    // Check command-line usage
    if (argc < 2) {
        printf("Usage:\n");
        printf("  ./cpu_sim <program_name>\n");
        printf("Example:\n");
        printf("  ./cpu_sim factorial\n");
        printf("  ./cpu_sim fibonacci\n");
        printf("  ./cpu_sim hello\n");
        return 1;
    }

    // ----------------------------------------------------------
    // 1️⃣ Prepare file names for assembler input/output
    // ----------------------------------------------------------
    char asmfile[64];
    char binfile[64];

    snprintf(asmfile, sizeof(asmfile), "%s.asm", argv[1]);
    snprintf(binfile, sizeof(binfile), "%s.txt", argv[1]);

    printf("\n[Main] Assembling program: %s -> %s\n", asmfile, binfile);

    // ----------------------------------------------------------
    // 2️⃣ Assemble the program (.asm → .txt)
    // ----------------------------------------------------------
    assemble_program(asmfile, binfile);

    // ----------------------------------------------------------
    // 3️⃣ Initialize CPU and memory
    // ----------------------------------------------------------
    CPU cpu;
    regs registers;
    pgm_segments segments;

    // Initialize components
    cpu.Register = &registers;
    cpu.segments = &segments;
    initialize_segments(&segments);
    initialize_registers(&registers);
    initialize_memory();
    io_init();
    cpu.pc = 0;
    cpu.flags = 0;

    printf("[Main] CPU initialized.\n");

    // ----------------------------------------------------------
    // 4️⃣ Load the binary file into CPU memory
    // ----------------------------------------------------------
    load_binary_into_cpu(&cpu, binfile);

    // ----------------------------------------------------------
    // 5️⃣ Run the program (fetch-decode-execute cycle)
    // ----------------------------------------------------------
    run_cpu(&cpu);

    // ----------------------------------------------------------
    // 6️⃣ Program complete
    // ----------------------------------------------------------
    printf("\n[Main] Execution finished.\n");
    return 0;
}

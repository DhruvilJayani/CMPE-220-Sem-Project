#include "compiler.h"
#include "encoder.h"
#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --------------------------------------------------
// Assemble a program (.asm -> .txt) using encoder.c
// --------------------------------------------------
void assemble_program(const char *asm_file, const char *bin_file) {
    FILE *fin = fopen(asm_file, "r");
    FILE *fout = fopen(bin_file, "w");

    if (!fin || !fout) {
        perror("[Compiler] Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[256];
    char mnemonic[32], op1[64], op2[64];
    int line_num = 0;

    printf("[Compiler] Assembling %s -> %s\n", asm_file, bin_file);

    while (fgets(line, sizeof(line), fin)) {
        // skip comments / blank lines
        if (line[0] == ';' || strlen(line) < 2)
            continue;

        if (!parse_asm_line(line, mnemonic, op1, op2))
            continue;

        int ok = 0;
        uint16_t instr = encode_line(mnemonic, op1, op2, &ok);

        if (!ok) {
            fprintf(stderr, "[Compiler] Error encoding line %d: %s", line_num, line);
            continue;
        }

        fprintf(fout, "%u\n", instr);
        line_num++;
    }

    fclose(fin);
    fclose(fout);

    printf("[Compiler] Assembled %d instructions successfully.\n", line_num);
}

// --------------------------------------------------
// Load a binary (.txt) file into CPU's text segment
// --------------------------------------------------
void load_binary_into_cpu(CPU *cpu, const char *bin_file) {
    FILE *file = fopen(bin_file, "r");
    if (!file) {
        perror("[Compiler] Error opening binary file");
        exit(EXIT_FAILURE);
    }

    char line[32];
    int i = 0;
    while (fgets(line, sizeof(line), file)) {
        if (strlen(line) < 1) continue;
        uint16_t instr = (uint16_t)strtoul(line, NULL, 10);
        cpu->segments->text_segment[i++] = instr;
    }

    fclose(file);
    printf("[Compiler] Loaded %d instructions into CPU memory.\n", i);
}

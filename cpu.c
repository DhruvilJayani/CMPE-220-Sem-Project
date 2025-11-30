// cpu.c
#include "alu.h"
#include "cpu.h"
#include "memory.h"
#include "program_layout.h"
#include <stdio.h>
#include <stdlib.h>

static int instr_count = 0;
void initialize_cpu(CPU* cpu) {
    cpu->pc = 0;
    cpu->flags = 0;
    cpu->sp = 0;
    for (int i = 0; i < MEMORY_SIZE; i++) cpu->memory[i] = 0;
}

void fetch_decode_execute(CPU* cpu, const char* binfile) {
    printf("Entered FDE cycle\n");
    
    word_t instruction=0;
    uint8_t addr_mode=0;
    uint8_t opcode=0;
    uint8_t dest=0;
    uint8_t src=0;

    instr_count = fetch_load_instr(cpu, binfile);
   
    //while(cpu->pc !=10) {
    while(!(cpu->flags&(1<<0))) {
    instruction = (cpu->segments->text_segment[cpu->pc]) & 0xFFFF;
    //printf("%d\n",instruction);
    addr_mode = (instruction >> 15) & 0b00001;
    opcode = (instruction >> 10) & 0b11111;
    dest = (instruction >> 5) & 0b11111;
    src = (instruction>>0) & 0b11111;
    //printf("src value %d\n", addr_mode);

    execute(cpu, opcode, addr_mode, dest, src);
    print_memory_layout(cpu->segments);
    if(cpu->flags & (1<<0)){
        printf("Done executing your code\n");
        break;
    }
    //cpu->pc++;
    }
    printf("result %d\n", cpu->memory[1]);
    //cpu->pc++;
}

static int fetch_load_instr(CPU* cpu, const char* binfile) {
    
    printf("Fetching binary instruction one by one\n");
    /*FILE *file = fopen(binfile, "r");
    if (!file) {
        perror("Failed to open the file");
        exit(EXIT_FAILURE);
    }*/
    printf("Opened file successfully\n");
    word_t instr;  // Buffer to store each line
    char line[17];
    int i =0;
     uint16_t binarySequence[19] = {
        0b1000100000100000,//LD R1, 0000
        0b0000100001000001,//LD R2, R1
        0b1000010001100001,//MOV R3, 1
        //0b0010100001000000,//PUSH R2
        //0b0010100010000000,//PUSH RA
        0b0010000010100000,//J factorial 5
        0b0010110010000000,//POP RA
        0b0010110001000000,//POP R2
        0b0001100001100010,//MUL R3 R2
        0b1010010001100100,//SW R3 0004
        0b0000000000000000,//HALT
        0b0010100001000000,//fact: PUSH R2
        0b0010100010000000,//PUSH RA
        0b1000110001000010,//CMP R2, 1
        0b0001110010100000,//BLE end
        0b1001010001000001,//SUB R2 1
        0b1010000011000000,//J fact
        0b0010110010000000,//POP RA
        0b0010110001000000,//POP R2
        0b0001100001100010,//MUL R3 R2
        0b0011000010000000};//end JR RA
        //0b1000100010001000,
        //0b0010010001100100};

    /*while (fgets(line, sizeof(line), file)) {
        instr = strtoul(line, NULL, 10);;
        printf("%s\n", line);  // Print the line
        cpu->segments->text_segment[i] = instr;
        i++;
    }*/
   for(i=0;i<19;i++) {
        instr = binarySequence[i];
        printf("%s\n", line);  // Print the line
        cpu->segments->text_segment[i] = instr;
        //i++;
   }
    return i;
}

void push(CPU *cpu, word_t value) {
    cpu->Register->SPR[1]--; // Decrement stack pointer
    cpu->memory[cpu->Register->SPR[1]] = value;
}

word_t pop(CPU *cpu) {
    word_t value = cpu->memory[cpu->Register->SPR[1]];
    cpu->Register->SPR[1]++; // Increment stack pointer
    return value;
}

/*word_t allocate_memory(CPU *cpu, word_t size) {
    static word_t heap_ptr = HEAP_START;
    word_t alloc_ptr = heap_ptr;
    heap_ptr += size;
    if (heap_ptr > HEAP_START + HEAP_SIZE) {
        printf("Out of memory\n");
        return 0;
    }
    return alloc_ptr;
}*/

void free_memory(CPU *cpu, word_t ptr) {
    // Simple free, no memory management
}

void print_cpu_state(CPU *cpu) {
    printf("CPU State:\n");
    for (int i = 0; i < 8; i++) {
        printf("R%d: 0x%08X\n", i, cpu->Register->GPR[i]);
    }
    printf("PC: 0x%08X\n", cpu->pc);
    printf("Flags: 0x%08X\n", cpu->flags);
}

void print_memory(CPU *cpu, uint16_t start, uint16_t end) {
    printf("Memory (0x%04X - 0x%04X):\n", start, end);
    for (uint16_t addr = start; addr <= end; addr++) {
        printf("0x%04X: 0x%08X\n", addr, cpu->memory[addr]);
    }
}
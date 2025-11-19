// cpu.h
#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include "memory.h"
#include "program_layout.h"

// -------------------------------
// Flag bit definitions
// -------------------------------
#define FLAG_CARRY   (1 << 0)
#define FLAG_ZERO    (1 << 0)
#define FLAG_NEG     (1 << 2)
#define FLAG_OVER    (1 << 3)
#define FLAG_HALT    (1 << 4)   // ✅ bit 4 used consistently
#define FLAG_LE   (1 << 0)   // result of last compare (≤)
#define FLAG_HALT (1 << 4)   // program stop



typedef uint16_t word_t;

#define HALT    (uint8_t)0b00000
#define MOV     (uint8_t)0b00001 
#define LD      (uint8_t)0b00010 
#define CMP     (uint8_t)0b00011
#define ADD     (uint8_t)0b00100 
#define SUB     (uint8_t)0b00101 
#define MUL     (uint8_t)0b00110
#define BLE     (uint8_t)0b00111 
#define J       (uint8_t)0b01000 
#define SW      (uint8_t)0b01001
#define PUSH    (uint8_t)0b01010
#define POP     (uint8_t)0b01011
#define JR      (uint8_t)0b01100

/*typedef enum {
    MOV = 0,
    LD,
    CMP,
    ADD,
    SUB,
    MUL,
    BLE,
    B,
    SW,
    PUSH,
    POP
} encode;*/

typedef struct {
    word_t pc;
    word_t flags;
    word_t sp;
    word_t memory[MEMORY_SIZE];
    regs   *Register;
    pgm_segments *segments;
} CPU;

void initialize_cpu(CPU *cpu);
void fetch_decode_execute(CPU* cpu, const char* binfile);
void print_cpu_state(CPU *cpu);
void print_memory(CPU *cpu, uint16_t start, uint16_t end);
static int fetch_load_instr(CPU* cpu, const char* binfile);

#endif
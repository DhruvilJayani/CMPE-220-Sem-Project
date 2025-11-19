#ifndef ENCODER_H
#define ENCODER_H

#include <stdint.h>

// 16-bit instruction format:
// [15] addr_mode | [14:10] opcode | [9:5] dest | [4:0] src

// Encodes a single assembly line into a 16-bit instruction
uint16_t encode_line(const char *mnemonic,
                     const char *op1,
                     const char *op2,
                     int *ok);

// Helper to parse one line of assembly into tokens
int parse_asm_line(const char *line,
                   char *mnemonic,
                   char *op1,
                   char *op2);

#endif

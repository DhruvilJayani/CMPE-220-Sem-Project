#include "encoder.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// --- opcodes must match cpu.h ---
enum {
  OP_HALT = 0b00000,
  OP_MOV  = 0b00001,
  OP_LD   = 0b00010,
  OP_CMP  = 0b00011,
  OP_ADD  = 0b00100,
  OP_SUB  = 0b00101,
  OP_MUL  = 0b00110,
  OP_BLE  = 0b00111,
  OP_J    = 0b01000,
  OP_SW   = 0b01001,
  OP_PUSH = 0b01010,
  OP_POP  = 0b01011,
  OP_JR   = 0b01100
};

// ------ small utilities ------
static int is_ws_only(const char *s) {
  while (*s) { if (!isspace((unsigned char)*s)) return 0; ++s; }
  return 1;
}

static int parse_reg(const char *s) {
  // expects "R<num>"
  if (s==NULL) return -1;
  if (s[0] != 'R' && s[0] != 'r') return -1;
  char *end;
  long v = strtol(s+1, &end, 10);
  if (*end != '\0' || v < 0 || v > 31) return -1;
  return (int)v;
}

static int parse_imm(const char *s, int *ok) {
  // accepts "#10", "10", "0x8000"
  *ok = 0;
  if (!s) return 0;
  int base = 10;
  const char *p = s;

  if (p[0] == '#') p++;
  if (p[0] == '0' && (p[1]=='x' || p[1]=='X')) { base = 16; p += 2; }

  char *end;
  long v = strtol(p, &end, base);
  if (*end != '\0') return 0;
  *ok = 1;
  return (int)v;
}

static int opcode_of(const char *mnem) {
  if (!mnem) return -1;
  if (!strcmp(mnem,"HALT")) return OP_HALT;
  if (!strcmp(mnem,"MOV"))  return OP_MOV;
  if (!strcmp(mnem,"LD"))   return OP_LD;
  if (!strcmp(mnem,"CMP"))  return OP_CMP;
  if (!strcmp(mnem,"ADD"))  return OP_ADD;
  if (!strcmp(mnem,"SUB"))  return OP_SUB;
  if (!strcmp(mnem,"MUL"))  return OP_MUL;
  if (!strcmp(mnem,"BLE"))  return OP_BLE;
  if (!strcmp(mnem,"J"))    return OP_J;
  if (!strcmp(mnem,"SW"))   return OP_SW;
  if (!strcmp(mnem,"PUSH")) return OP_PUSH;
  if (!strcmp(mnem,"POP"))  return OP_POP;
  if (!strcmp(mnem,"JR"))   return OP_JR;
  return -1;
}

// ------ public: parse one asm line into tokens ------
int parse_asm_line(const char *line, char *mnemonic, char *op1, char *op2) {
  // strip comment starting with ';'
  char buf[256];
  size_t n = 0;
  while (line[n] && line[n] != ';' && n < sizeof(buf)-1) { buf[n] = line[n]; n++; }
  buf[n] = '\0';
  if (is_ws_only(buf)) return 0;

  // tokenize: MNEMONIC [OP1] [, OP2]
  char m[32]={0}, a[64]={0}, b[64]={0};
  // first replace comma with space to simplify
  for (char *p = buf; *p; ++p) if (*p==',') *p = ' ';
  int cnt = sscanf(buf, " %31s %63s %63s", m, a, b);
  if (cnt <= 0) return 0;

  // copy out
  strcpy(mnemonic, m);
  if (cnt >= 2) strcpy(op1, a); else op1[0] = '\0';
  if (cnt >= 3) strcpy(op2, b); else op2[0] = '\0';
  return 1;
}

// ------ public: encode tokens to 16-bit instruction ------
uint16_t encode_line(const char *mnemonic,
                     const char *op1,
                     const char *op2,
                     int *ok) {
  *ok = 0;

  int op = opcode_of(mnemonic);
  if (op < 0) return 0;

  // defaults
  int addr_mode = 0;
  int dest = 0;
  int src  = 0;

  // HALT has no operands
  if (op == OP_HALT) {
    *ok = 1;
  }
  // Branch / Jump: operand is an IMMEDIATE TARGET in DEST field
  else if (op == OP_BLE || op == OP_J) {
    int imm_ok = 0;
    int imm = parse_imm(op1, &imm_ok);
    if (!imm_ok) return 0;
    addr_mode = 1;          // immediate target
    dest = imm & 0x1F;      // 5-bit DEST field
    src  = 0;
    *ok = 1;
  }
  // PUSH/POP/JR – single register (only the patterns you use)
  else if (op == OP_PUSH || op == OP_POP || op == OP_JR) {
    int r = parse_reg(op1);
    if (r < 0) return 0;
    addr_mode = 0;
    dest = r;
    src  = 0;
    *ok = 1;
  }
  // Two-operand ALU/memory
  else {
    // dest must be a register for these forms you use
    int rd = parse_reg(op1);
    if (rd < 0) return 0;
    dest = rd;

    // src can be register or immediate
    int rs = parse_reg(op2);
    if (rs >= 0) {
      addr_mode = 0;
      src = rs;
      *ok = 1;
    } else {
      int imm_ok = 0;
      int imm = parse_imm(op2, &imm_ok);
      if (!imm_ok) return 0;
      addr_mode = 1;
      src = imm & 0x1F;
      *ok = 1;
    }
  }

  uint16_t instr = 0;
  instr |= (addr_mode & 0x1) << 15;
  instr |= (op        & 0x1F) << 10;
  instr |= (dest      & 0x1F) << 5;
  instr |= (src       & 0x1F) << 0;
  return instr;
}

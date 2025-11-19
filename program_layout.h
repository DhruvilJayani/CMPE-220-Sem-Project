/* program_layout.h */

#ifndef PROGRAM_LAYOUT_H
#define PROGRAM_LAYOUT_H

#include <stdint.h>

/* Define memory segments */
#define TEXT_SEGMENT_START 0x0000
#define TEXT_SEGMENT_SIZE  0x2000  // 8KB

#define DATA_SEGMENT_START 0x2000
#define DATA_SEGMENT_SIZE  0x2000  // 8KB

#define HEAP_SEGMENT_START 0x4000
#define HEAP_SEGMENT_SIZE  0x1000  // 4KB

#define STACK_SEGMENT_START 0xF000
#define STACK_SEGMENT_SIZE  0x1000  // 4KB
#define STACK_START (STACK_SEGMENT_START + STACK_SEGMENT_SIZE - 1)

/* Memory structure to simulate program layout */
typedef struct {
    uint16_t text_segment[TEXT_SEGMENT_SIZE];  // Text (code) segment
    uint16_t data_segment[DATA_SEGMENT_SIZE];  // Data segment
    uint16_t heap_segment[HEAP_SEGMENT_SIZE];  // Heap segment
    uint16_t stack_segment[STACK_SEGMENT_SIZE];  // Stack segment
} pgm_segments;

/* Function prototypes */
void initialize_segments(pgm_segments* segments);

void print_memory_layout(pgm_segments* segments);

#endif /* PROGRAM_LAYOUT_H */

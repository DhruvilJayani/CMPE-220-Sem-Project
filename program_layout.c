

#include <stdio.h>
#include <string.h> // For memset
#include "program_layout.h"

uint8_t *stack_pointer = (uint8_t *)STACK_START;


/* Initialize all memory segments to zero */
void initialize_segments(pgm_segments* segments) {
    memset(segments->text_segment, 0, TEXT_SEGMENT_SIZE);
    memset(segments->data_segment, 0, DATA_SEGMENT_SIZE);
    memset(segments->heap_segment, 0, HEAP_SEGMENT_SIZE);
    memset(segments->stack_segment, 0, STACK_SEGMENT_SIZE);
}

void print_memory_layout(pgm_segments* segments) {
    printf("Memory Layout with Values:\n");
    printf("-----------------------------\n");

    printf("Stack Segment\n");
    printf("-------------\n");
    for(int i = 0;i<10;i++) {
        //if(segments->stack_segment[STACK_SEGMENT_START + STACK_SEGMENT_SIZE - 0]==0) break;
        printf("%d\n", segments->stack_segment[i]);
    }
    printf("Heap Segment\n");
    printf("-------------\n");
    for(int i = 0;i<10;i++) {
        if(segments->heap_segment[i]==0) break;
        printf("%d\n", segments->heap_segment[i]);
    }
    printf("Data Segment\n");
    printf("-------------\n");
    for(int i = 0;i<10;i++) {
        if(segments->data_segment[i]==0) break;
        printf("%d\n", segments->data_segment[i]);
    }
    printf("Text Segment\n");
    printf("-------------\n");
    for(int i = 0;i<17;i++) {
        //if(segments->text_segment[i]==0) break;
        printf("%d\n", segments->text_segment[i]);
    }
    printf("--------------\n");
    printf("\n\n\n");
}
; hello.asm – writes ASCII codes for "HELLO\n" into memory
; Works with current 5-bit immediate assembler (no UART needed)

; R1 = memory pointer
; R2 = character register

MOV R1, #0      ; start writing at memory[0]

; H
MOV R2, #72
SW R2, R1
ADD R1, #1

; E
MOV R2, #69
SW R2, R1
ADD R1, #1

; L
MOV R2, #76
SW R2, R1
ADD R1, #1

; L
MOV R2, #76
SW R2, R1
ADD R1, #1

; O
MOV R2, #79
SW R2, R1
ADD R1, #1

; newline (\n)
MOV R2, #10
SW R2, R1

HALT

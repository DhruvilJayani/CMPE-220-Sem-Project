; factorial.asm – manual numeric jumps (no labels)
; Demonstrates recursion-like stack usage (conceptually)
; R1 = n, R2 = result, R3 = temp, R5 = stack pointer, R6 = constant 1

MOV R1, #5       ; n = 5
MOV R2, #1       ; result = 1
MOV R5, #20      ; stack pointer = 20
MOV R6, #1       ; const 1
J #6             ; jump to factorial body
HALT             ; 5  end of program (never hit directly)

; 6: factorial_start
CMP R1, #1       ; 6  compare n <= 1
BLE #18          ; 7  if yes, go to factorial_end
SW R1, R5        ; 8  push n
ADD R5, #1       ; 9
SUB R1, #1       ;10
J #6             ;11 recursive call
SUB R5, #1       ;12 pop (conceptually)
LD R3, R5        ;13 load popped n
MUL R2, R3       ;14 result *= n
J #6             ;15 repeat until n<=1 (simulate recursion collapse)
; 16 unused
; 17 unused
MOV R2, #1       ;18 factorial_end: base case result = 1
HALT             ;19 stop

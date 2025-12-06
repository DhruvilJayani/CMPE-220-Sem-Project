; factorial.asm – manual numeric jumps (no labels)
; Demonstrates recursion with proper stack usage
; R1 = n (current value), R2 = result, R3 = temp, R4 = recursion depth counter
; R5 = stack pointer, R6 = constant 1

MOV R1, #7       ; n = 5
MOV R2, #1       ; result = 1
MOV R4, #0       ; depth counter = 0
MOV R5, #100     ; stack pointer = 100
MOV R6, #1       ; constant 1
J #7             ; jump to factorial_push
HALT             ; 6  end of program

; 7: factorial_push (recursion descent - push phase)
CMP R1, R6       ; 7  compare n <= 1
BLE #14          ; 8  if yes, start unwinding (factorial_pop)
SW R1, R5        ; 9  push current n onto stack
ADD R5, #1       ;10  increment stack pointer
ADD R4, #1       ;11  increment depth counter
SUB R1, #1       ;12  n = n - 1
J #7             ;13  recursive call (continue descending)

; 14: factorial_pop (recursion ascent - pop and multiply phase)
CMP R4, #0       ;14  check if depth counter = 0
BLE #21          ;15  if yes, done - jump to end
SUB R5, #1       ;16  decrement stack pointer
LD R3, R5        ;17  pop n value from stack
MUL R2, R3       ;18  result = result * n
SUB R4, #1       ;19  decrement depth counter
J #14            ;20  continue unwinding
HALT             ;21  end - result in R2

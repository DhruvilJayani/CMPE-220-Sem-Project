; fibonacci.asm - generates first 10 Fibonacci numbers and halts correctly
; Uses registers:
; R1 = previous term
; R2 = current term
; R3 = loop counter
; R4 = limit (10)
; R5 = memory index
; R6 = temp (sum)

MOV R1, #0      ; prev = 0
MOV R2, #1      ; curr = 1
MOV R3, #0      ; counter = 0
MOV R4, #10     ; limit = 10
MOV R5, #0      ; memory index = 0
MOV R6, #0      ; temp = 0

; ---------- loop start @0006 ----------
CMP R3, R4          ; compare counter <= limit
BLE #9              ; if true, go compute next number
J #18               ; else jump to HALT

; ---------- compute next @0009 ----------
MOV R6, #0          ; reset temp each iteration
ADD R6, R1          ; temp = R1
ADD R6, R2          ; temp = R1 + R2
MOV R1, R2          ; shift forward
MOV R2, R6          ; new current term
SW R2, R5           ; store R2 into memory[address in R5]
ADD R5, #1          ; move to next memory address
ADD R3, #1          ; increment counter
J #6                ; jump back to compare

; ---------- program end @0018 ----------
HALT

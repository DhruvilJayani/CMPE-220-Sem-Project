; factorial.asm – factorial using stack + two phases
; R1 = n, R2 = result, R3 = temp, R4 = depth, R5 = SP, R6 = 1

MOV R1, #7       ; n = 7 (change to 5 for 5!)
MOV R2, #1       ; result = 1
MOV R4, #0       ; depth = 0
MOV R5, #100     ; stack base
MOV R6, #1       ; constant 1
J #7             ; go to push phase
HALT             ; (unused safety end)

; ---- push phase: "recursive descent" ----
; while (n > 1) push n, depth++, n--
CMP R1, R6       ; 7  if n <= 1 → done descending
BLE #14          ; 8  jump to pop phase
SW R1, R5        ; 9  stack[SP] = n
ADD R5, #1       ;10 SP++
ADD R4, #1       ;11 depth++
SUB R1, #1       ;12 n--
J #7             ;13 loop

; ---- pop phase: "recursive unwind" ----
; while (depth > 0) { SP--, result *= stack[SP], depth-- }
CMP R4, #0       ;14 if depth == 0 → done
BLE #21          ;15 jump to final HALT
SUB R5, #1       ;16 SP--
LD  R3, R5       ;17 temp = stack[SP]
MUL R2, R3       ;18 result *= temp
SUB R4, #1       ;19 depth--
J #14            ;20 loop
HALT             ;21 end, R2 holds n!

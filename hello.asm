; hello.asm – builds ASCII manually to get real output values
; R1 = memory index
; R2 = character builder register

MOV R1, #0      ; memory pointer = 0

; ---------------- H (72) ----------------
MOV R2, #31
ADD R2, #31     ; 31 + 31 = 62
ADD R2, #10     ; 62 + 10 = 72
SW R2, R1
ADD R1, #1

; ---------------- E (69) ----------------
MOV R2, #31
ADD R2, #31     ; 62
ADD R2, #7      ; 62 + 7 = 69
SW R2, R1
ADD R1, #1

; ---------------- L (76) ----------------
MOV R2, #31
ADD R2, #31     ; 62
ADD R2, #14     ; 62 + 14 = 76
SW R2, R1
ADD R1, #1

; ---------------- L (76) AGAIN ----------
MOV R2, #31
ADD R2, #31
ADD R2, #14
SW R2, R1
ADD R1, #1

; ---------------- O (79) ----------------
MOV R2, #31
ADD R2, #31     ; 62
ADD R2, #17     ; 62 + 17 = 79
SW R2, R1
ADD R1, #1

; ---------------- newline (10) ----------
MOV R2, #10
SW R2, R1

HALT

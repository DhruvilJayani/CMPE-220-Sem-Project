; timer_demo.asm – working software timer loop
; R1 = pseudo timer counter
; R2 = total iterations
; R3 = loop counter
; R4 = temp
; R5 = memory index

MOV R1, #0      ; timer = 0
MOV R2, #5      ; limit = 5
MOV R3, #0      ; counter = 0
MOV R5, #0      ; memory index = 0

; ---------- loop start @0004 ----------
CMP R3, R2          ; compare counter <= limit
BLE #7              ; if true, execute body
J #15               ; else HALT

; ---------- body @0007 ----------
ADD R1, #1          ; increment pseudo timer
MOV R4, R1          ; copy timer to R4
SW R4, R5           ; store timer value in memory[ R5 ]
ADD R5, #1          ; advance memory pointer
ADD R3, #1          ; counter++
J #4                ; back to compare

; ---------- end @0015 ----------
HALT

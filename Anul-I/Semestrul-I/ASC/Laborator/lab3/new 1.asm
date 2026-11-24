bits 32 

global start        

extern exit               
import exit msvcrt.dll    

segment data use32 class=data
    a dd 125
    b db 2
    c dw 15
    d db 200
    e dq 80

    ; a + b / c - d * 2 - e, fara semn
segment code use32 class=code
    start:
        ; b / c
        mov AL, [b] ; AL = b = 0000 0010b
        mov AH, 0   ; AX = b = 0000 0000 0000 0010b (fara semn)
        mov DX, 0   ; DX:AX = b
        div word [c]; AX = b / c si DX = b % c
        
        mov BX, AX  ; salvam rezultatul (catul) in alt registru
        
        mov AL, 2
        mul byte [d]; AX = d * 2
        
        sub bx, ax  ; BX = b / c - d * 2
        
        ; a + ...
        ; mov eax, 0
        ; mov ax, bx  ; EAX =  b / c - d * 2
        ; add eax, [a]; EAX = a + b / c - d * 2
        
    
        ; exit(0)
        push    dword 0
        call    [exit]
        
        ; tema 14

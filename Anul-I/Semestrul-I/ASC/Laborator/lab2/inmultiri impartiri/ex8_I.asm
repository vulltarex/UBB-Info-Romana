bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 2
    b db 3
    c db 0A2h
    d dw 02AF3h

; our code starts here
;(100*a+d+5-75*b)/(c-5)
segment code use32 class=code
    start:
        mov AL, 100
        mul byte [a]
        add AX, [d]
        add AX, 5
        mov BX, AX
        
        mov AL, 75
        mul byte [b]
        sub BX, AX
        
        mov AX, BX
        mov BL, [c]
        sub BL, 5
        div BL
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

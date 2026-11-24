bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; a - byte, b - word, c - double word, d - qword - Interpretare fara semn
segment data use32 class=data
    a db 12h
    b dw 0E9ABh
    c dd 1258FFh
    d dq 84ECNN0001h
    x resd 2

; (a+d)-(c-b)+c
segment code use32 class=code
    start:
        ; (a + d)
        mov eax, 0
        mov al, [a]
        mov edx, 0  ;EDX:EAX = a
        mov ecx, [d]
        mov ebx, [d + 4]    ; EBX:ECX = d
        add ecx, eax
        adc ebx, edx    ; EBX:ECX = a + d 
        
        ; (c - b)
        mov eax, 0
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

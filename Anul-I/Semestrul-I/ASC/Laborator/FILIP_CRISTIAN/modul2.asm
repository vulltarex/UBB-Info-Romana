bits 32

global _afisare_suma
extern _printf


segment data use32 class=data
    format db "%d", 0

segment code public code use32
    _afisare_suma:
        push ebp
        mov ebp, esp
        
        mov eax, [ebp + 8]
        
        push eax
        push format
        call _printf
        add esp, 4*2
        
        mov esp, ebp
        pop ebp
        
        ret
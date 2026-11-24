bits 32

global _cifra_sute

segment code public code use32
    _cifra_sute:
        ;cod intrare
        push ebp
        mov ebp, esp
        
        mov eax, [ebp + 8]
        mov ebx, 100
        xor edx, edx
        div ebx
        mov ebx, 10
        xor edx, edx
        div ebx
        mov eax, edx
        
        ;cod iesire
        mov esp, ebp
        pop ebp
        
        ret
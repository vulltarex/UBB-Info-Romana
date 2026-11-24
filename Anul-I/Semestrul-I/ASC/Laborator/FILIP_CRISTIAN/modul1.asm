bits 32

global _verifica_numar

segment data use32 class=data
    suma dd 0

segment code public code use32
    _verifica_numar:
        push ebp
        mov ebp, esp
        push ebx
        push ecx
        
        mov ebx, 0
        mov ecx, 0
        mov eax, [ebp+8]
        rol eax, 1
        test eax, 1
        jnz next
        ror eax, 1
    
    verif:
        mov bl, al
        and bl, 1111b
        cmp bl, 0
        je next
        add [suma], bl
        inc ecx
        shr eax, 4
        jmp verif
    
    next:
        mov eax, 0
        cmp [ebp + 12], ecx
        ja final
        mov eax, [suma]
    
    final:
        
        pop ecx
        pop ebx
        mov esp, ebp
        pop ebp
        
        ret
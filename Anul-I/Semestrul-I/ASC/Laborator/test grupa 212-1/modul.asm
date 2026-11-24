bits 32

global _lungime_para
global _rotire

segment code public code use32
    _lungime_para:
        push ebp
        mov ebp, esp
        push esi
        push ebx
        
        mov esi, [ebp+8]
        mov ebx, esi
        
    cauta_final:
        cmp byte [esi], 0
        je final1
        inc esi
        jmp cauta_final
        
    final1:
        sub esi, ebx
        mov eax, esi
        and eax, 1
        xor eax, 1
        
        pop ebx
        pop esi
        mov esp, ebp
        pop ebp
        
        ret
        
    _rotire:
        push ebp
        mov ebp, esp
        push esi
        push edi
        push ebx
        mov esi, [ebp + 8]
        mov ebx, esi
    
    lungime:
        cmp byte [esi], 0
        je next
        inc esi
        jmp lungime
        
    next:
        sub esi, ebx
        mov ecx, esi
        
        mov ebx, [ebp + 8]
        mov al, [ebx]
        
        mov edi, [ebp + 8]
        mov esi, edi
        inc esi
        dec ecx
        jecxz final2
        rep movsb
        
    final2:
        stosb
        pop ebx
        pop edi
        pop esi
        
        mov esp, ebp
        pop ebp
        
        ret
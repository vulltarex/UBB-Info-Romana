bits 32

global _procesare

segment code public code use32
    _procesare:
        push ebp
        mov ebp, esp
        push ecx
        push esi
        push edi
        push eax
        push ebx
        mov esi, [ebp + 8]
        
    cautare_cuvinte:
        cmp byte [esi], 0
        je final
        mov ecx, 0
        mov edi, esi
        cautare_spatiu:
            cmp byte [edi], ' '
            mov ebx, edi
            je prelucrare
            cmp byte [edi], 0
            je prelucrare
            inc edi
            inc ecx
            jmp cautare_spatiu
        prelucrare:
            push edi
            cmp esi, edi
            jge next
            mov al, [esi]
            xchg al, [edi]
            mov [esi], al
            inc esi
            dec edi
            pop edi
            cmp byte [edi], 0
            je final
            jmp prelucrare
        next:
            mov esi, ebx
            inc esi
            jmp cautare_cuvinte
    final:
        pop ebx
        pop eax
        pop edi
        pop esi
        pop ecx
        mov esp, ebp
        pop ebp
        
        ret
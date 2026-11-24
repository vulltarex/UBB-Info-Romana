bits 32

global _suma


segment code public code use32
    _suma:
        
        push ebp
        mov ebp, esp
        
        mov eax, 0
        add eax, [esp + 8]
        add eax, [esp + 12]
        add eax, [esp + 16]
        
        mov esp, ebp
        pop ebp
        
        ret

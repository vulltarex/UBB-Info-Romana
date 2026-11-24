bits 32

global start        

extern exit, scanf, fopen, fclose, fprintf        
import exit msvcrt.dll
import scanf msvcrt.dll    
import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll

segment data use32 class=data
    n dd 0
    l dd 0
    cuv resd 30
    mod_acces db "w", 0
    format_n db "%d", 0
    format_l db "%c", 0
    format_cuv db "%s", 0
    
    nume_fis db "out.txt", 0
    descriptor_fis db -1
    ;Citeste de la tastatura in mod repetat, un nr natural n, o litera l si un cuvant
    ;scrieti in fisier doar acele cuvinte care au litera l si sunt formate din l litere
    ;fisierul se va numi "out.txt" si se va suprascrie la fiecare rulare
    ;citirea se termina la n=0

segment code use32 class=code
    start:
        push mod_acces
        push nume_fis
        call [fopen]
        add esp, 4*2
        
        mov [descriptor_fis], eax
        cmp eax, 0
        je final
        
        citire:
            push n
            push format_n
            call [scanf]
            add esp, 4*2
            
            cmp dword [n], 0
            je gata_citire
            
            push l
            push format_l
            call [scanf]
            add esp, 4*2
            
            push cuv
            push format_cuv
            call [scanf]
            add esp, 4*2
            
            push cuv
            push format_cuv
            push dword [descriptor_fis]
            call [fprintf]
            add esp, 4*3
                
            jmp citire
        
        gata_citire:
            push dword [descriptor_fis]
            call [fclose]
            add esp, 4
        
       final:
        push    dword 0
        call    [exit]

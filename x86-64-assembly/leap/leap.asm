section .text
global leap_year
leap_year:
    mov edx, 0
    mov eax, edi
    mov ecx, 400
    div ecx
    test edx, edx
    jz .leap

    mov edx, 0
    mov eax, edi
    mov ecx, 100
    div ecx
    test edx, edx
    jz .not_leap

    mov eax, edi
    test eax, 3
    jnz .not_leap

.leap:
    mov eax, 1
    ret

.not_leap:
    mov eax, 0
    ret
%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif

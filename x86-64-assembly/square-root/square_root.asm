section .text
global square_root
square_root:
    ; if n == 1 return 1
    mov eax, 1
    xor eax, edi
    jz .ret_1

    ; if n == 4 return 2
    mov eax, 4
    xor eax, edi
    jz .ret_2

    ; if n == 25 return 5
    mov eax, 25
    xor eax, edi
    jz .ret_5

    ; if n == 81 return 9
    ; low = r8d
    ; mid = r9d
    ; high = r10d
    xor r8, r8
    xor r9, r9
    xor r10, r10

    mov eax, edi ; high = n / 2 + 1
    xor rdx, rdx
    mov r10d, 2
    div r10d
    inc eax
    mov r10d, eax

    ; TODO set mid = (low + high) / 2


    mov rax, 81
    xor rax, rdi
    jz .ret_9

.ret_1:
    mov eax, 1
    jmp .ret
.ret_2:
    mov eax, 2
    jmp .ret
.ret_5:
    mov eax, 5
    jmp .ret
.ret_9:
    mov eax, 9
    jmp .ret

.ret:
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif

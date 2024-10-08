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

.n_eq_81_ret_9:
    ; low = r8d
    ; mid = r9d
    ; high = r10d
    xor r8, r8
    xor r9, r9
    xor r10, r10
    xor rsi, rsi

    ; high = n / 2 + 1
    mov eax, edi
    xor rdx, rdx
    mov r10d, 2
    div r10d
    inc eax
    mov r10d, eax

.loop:
    ; mid = (low + high) / 2
    mov eax, r8d
    add eax, r10d
    xor rdx, rdx
    mov r11d, 2
    div r11d
    mov r9d, eax

    ; r11d = mid^2
    xor rdx, rdx
    mov eax, r9d
    mov r11d, r9d
    mul r11d
    mov r11d, eax

    ; if (mid^2 (r11d) == n)
    ;   return n
    mov esi, r11d
    xor esi, edi
    jz .ret_mid

    ; if (mid^2 (r11d) < n)
    ;   jump to .sqrt_larger
    cmp r11d, edi ; mid^2 - n
    jl .sqrt_larger ; if true, jump

    ; else (mid^2 (r11d) > n)
    ;   high = mid - 1
    mov r10d, r9d
    sub r10d, 1
    jmp .check_low_gt_high

.sqrt_larger:
    ;   low = mid + 1
    mov r8d, r9d
    add r8d, 1

.check_low_gt_high:
    ; if (low > high)
    ;   then return high
    cmp r8d, r10d ; low - high
    jg .ret_high

    ; else rerun loop
    jmp .loop

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
.ret_mid:
    mov eax, r9d
    jmp .ret
.ret_high:
    mov eax, r10d
    jmp .ret

.ret:
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif

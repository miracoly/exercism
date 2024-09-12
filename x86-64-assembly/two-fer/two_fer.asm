section .data
    first_part    db 'One for ', 0           ; "One for "
    second_part   db ', one for me.', 0      ; ", one for me."
    you           db 'you', 0                ; Default name "you"

section .text
    global two_fer
two_fer:
    ; rdi: pointer to name (can be NULL)
    ; rsi: pointer to buffer where the result will be stored

    ; Check if buffer pointer (rsi) is NULL
    test rsi, rsi
    je _ret                             ; If NULL, exit the function

    ; Initialize source and destination pointers
    lea rdx, [rel first_part]           ; rdx points to "One for "
    mov rcx, rsi                        ; rcx points to the buffer (destination)

    ; --------- Copy "One for " ---------
.copy_first_part:
    call copy_string

    dec rcx  ; Move back to overwrite the null terminator

    ; --------- Decide on Name or "you" ---------
    test rdi, rdi          ; Check if name is provided
    jne .copy_name         ; If name is provided, jump to copy it
    lea rdx, [rel you]     ; Else, point rdx to "you"
    jmp .copy_name_common  ; Jump to common copy routine

.copy_name:
    mov rdx, rdi           ; rdx points to the provided name

.copy_name_common:
.copy_name_loop:
    call copy_string

    ; --------- Append ", one for me." ---------
    ; At this point, rcx points to the null terminator after the name
    ; We need to overwrite the null terminator to append the second part
    dec rcx                               ; Move back to overwrite the null

    lea rdx, [rel second_part]            ; rdx points to ", one for me."

.copy_second_part:
    call copy_string

    ; --------- Function Return ---------
_ret:
    ret

copy_string:
    mov al, [rdx]
    mov [rcx], al
    inc rdx
    inc rcx
    test al, al
    jne copy_string
    ret

%ifidn __OUTPUT_FORMAT__,elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
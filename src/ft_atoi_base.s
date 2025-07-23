section .text
    global ft_atoi_base

; int ft_atoi_base(char *str, char *base)
; rdi = str, rsi = base
ft_atoi_base:
    push rbp
    mov rbp, rsp
    sub rsp, 32                 ; Local variables space
    push rbx
    push r12
    push r13
    push r14
    push r15
    
    mov r12, rdi                ; r12 = str
    mov r13, rsi                ; r13 = base
    
    ; Check if base is valid
    mov rdi, r13
    call base_check_failed
    test eax, eax
    jnz .return_zero
    
    ; Initialize variables
    mov dword [rbp-4], 1        ; sign = 1
    lea rsi, [rbp-4]            ; &sign
    mov rdi, r12                ; str
    call strip_spaces_sign
    mov r14d, eax               ; r14 = index
    
    ; Calculate base_num (strlen of base)
    mov r15, 0                  ; base_num = 0
.count_base:
    movzx eax, byte [r13 + r15]
    test al, al
    jz .count_done
    inc r15
    jmp .count_base
.count_done:
    ; r15 = base_num
    
    mov rbx, 0                  ; sum = 0
    
.convert_loop:
    ; Check if current char is in base
    movzx edi, byte [r12 + r14] ; str[index]
    mov rsi, r13                ; base
    call is_included
    cmp eax, -1
    je .conversion_done
    
    ; sum = sum * base_num + digit_value
    mov rcx, rax                ; rcx = digit_value (from is_included return)
    mov rax, rbx
    mul r15                     ; rax = sum * base_num
    mov rbx, rax
    add rbx, rcx                ; rbx += digit_value
    inc r14d                    ; index++
    jmp .convert_loop
    
.conversion_done:
    ; Apply sign
    mov eax, dword [rbp-4]      ; sign
    imul rbx, rax               ; sum *= sign
    mov rax, rbx
    jmp .exit
    
.return_zero:
    xor eax, eax
    
.exit:
    pop r15
    pop r14
    pop r13
    pop r12
    pop rbx
    leave
    ret

; int strip_spaces_sign(char *str, int *sign)
; rdi = str, rsi = sign
strip_spaces_sign:
    push rbp
    mov rbp, rsp
    push rbx
    
    mov rbx, rsi                ; rbx = sign pointer
    xor eax, eax                ; i = 0
    
.skip_spaces:
    movzx ecx, byte [rdi + rax]
    ; Check if char is whitespace ('\t' to '\r' or ' ')
    cmp cl, 0x09                ; '\t'
    jl .check_space
    cmp cl, 0x0D                ; '\r'
    jle .is_space
.check_space:
    cmp cl, 0x20                ; ' '
    jne .spaces_done
.is_space:
    inc eax
    jmp .skip_spaces
    
.spaces_done:
    mov dword [rbx], 1          ; *sign = 1
    
.sign_loop:
    movzx ecx, byte [rdi + rax]
    cmp cl, '+'
    je .plus_sign
    cmp cl, '-'
    je .minus_sign
    jmp .sign_done
    
.plus_sign:
    inc eax
    jmp .sign_loop
    
.minus_sign:
    neg dword [rbx]             ; *sign *= -1
    inc eax
    jmp .sign_loop
    
.sign_done:
    pop rbx
    leave
    ret

; int is_included(char s, char *base)
; rdi = s (char), rsi = base
is_included:
    push rbp
    mov rbp, rsp
    
    xor eax, eax                ; i = 0
    
.search_loop:
    movzx ecx, byte [rsi + rax]
    test cl, cl
    jz .not_found
    
    cmp dil, cl                 ; Compare s with base[i]
    je .found
    
    inc eax
    jmp .search_loop
    
.found:
    ; Return index (already in eax)
    leave
    ret
    
.not_found:
    mov eax, -1
    leave
    ret

; int base_check_failed(char *base)
; rdi = base
base_check_failed:
    push rbp
    mov rbp, rsp
    push rbx
    push r12
    
    mov rbx, rdi                ; rbx = base
    
    ; Count base length
    xor eax, eax                ; i = 0
.count_loop:
    movzx ecx, byte [rbx + rax]
    test cl, cl
    jz .count_done
    inc eax
    jmp .count_loop
.count_done:
    ; Check if length <= 1
    cmp eax, 1
    jle .return_fail
    
    mov r12d, eax               ; r12 = base_len
    xor eax, eax                ; i = 0
    
.outer_loop:
    cmp eax, r12d
    jge .check_passed
    
    ; Check if base[i] is valid character
    movzx edi, byte [rbx + rax]
    push rax
    call valid_char_failed
    pop rcx                     ; Restore i to rcx
    test eax, eax
    jnz .return_fail
    
    ; Check for duplicates
    mov edx, ecx                ; j = i + 1
    inc edx
.inner_loop:
    cmp edx, r12d
    jge .inner_done
    
    movzx esi, byte [rbx + rcx] ; base[i]
    movzx edi, byte [rbx + rdx] ; base[j]
    
    ; Check if base[i] == base[j]
    cmp esi, edi
    je .return_fail
    
    ; Check if base[j] is valid
    push rcx
    push rdx
    call valid_char_failed
    pop rdx
    pop rcx
    test eax, eax
    jnz .return_fail
    
    inc edx
    jmp .inner_loop
    
.inner_done:
    inc ecx
    mov eax, ecx
    jmp .outer_loop
    
.check_passed:
    xor eax, eax                ; Return 0 (success)
    jmp .exit
    
.return_fail:
    mov eax, 1                  ; Return 1 (fail)
    
.exit:
    pop r12
    pop rbx
    leave
    ret

; int valid_char_failed(char s)
; rdi = s (char)
valid_char_failed:
    push rbp
    mov rbp, rsp
    
    ; Check if s == '+' or s == '-'
    cmp dil, '+'
    je .return_fail
    cmp dil, '-'
    je .return_fail
    
    ; Check if s <= ' ' (0x20)
    cmp dil, 0x20
    jle .return_fail
    
    ; Check if s == 127 (DEL)
    cmp dil, 127
    je .return_fail
    
    ; Character is valid
    xor eax, eax
    leave
    ret
    
.return_fail:
    mov eax, 1
    leave
    ret
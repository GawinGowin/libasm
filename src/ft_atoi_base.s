section .text
    global ft_atoi_base
    extern ft_isspace
    extern ft_strchr
    extern ft_strspn

ft_atoi_base:
    push rbp
    mov rbp, rsp
    sub rsp, 32
    push rbx
    push r12
    push r13
    push r14
    push r15
    
    mov r12, rdi
    mov r13, rsi
    
    mov rdi, r13
    call base_check_failed
    test eax, eax
    jnz .return_zero
    
    mov dword [rbp-4], 1
    lea rsi, [rbp-4]
    mov rdi, r12
    call strip_spaces_sign
    mov r14d, eax
    
    mov r15, 0
.count_base:
    movzx eax, byte [r13 + r15]
    test al, al
    jz .count_done
    inc r15
    jmp .count_base
.count_done:
    
    mov rbx, 0
    
.convert_loop:
    movzx edi, byte [r12 + r14]
    mov rsi, r13
    call is_included
    cmp eax, -1
    je .conversion_done
    
    mov rcx, rax
    mov rax, rbx
    mul r15
    mov rbx, rax
    add rbx, rcx
    inc r14d
    jmp .convert_loop
    
.conversion_done:
    mov eax, dword [rbp-4]
    imul rbx, rax
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

strip_spaces_sign:
    push rbp
    mov rbp, rsp
    push rbx
    push r12
    
    mov rbx, rsi
    mov r12, rdi
    xor eax, eax
    
.skip_spaces:
    movzx edi, byte [r12 + rax]
    push rax
    call ft_isspace
    pop rcx
    test eax, eax
    jz .spaces_done
    inc rcx
    mov eax, ecx
    jmp .skip_spaces
    
.spaces_done:
    mov dword [rbx], 1
    mov eax, ecx
    
.sign_loop:
    movzx edx, byte [r12 + rax]
    cmp dl, '+'
    je .plus_sign
    cmp dl, '-'
    je .minus_sign
    jmp .sign_done
    
.plus_sign:
    inc eax
    jmp .sign_loop
    
.minus_sign:
    neg dword [rbx]
    inc eax
    jmp .sign_loop
    
.sign_done:
    pop r12
    pop rbx
    leave
    ret

is_included:
    push rbp
    mov rbp, rsp
    push rbx
    push r12
    
    mov bl, dil
    mov r12, rsi
    mov rdi, rsi
    movzx esi, bl
    call ft_strchr
    
    test rax, rax
    jz .not_found
    
    sub rax, r12
    jmp .done
    
.not_found:
    mov eax, -1
    
.done:
    pop r12
    pop rbx
    leave
    ret

base_check_failed:
    push rbp
    mov rbp, rsp
    push rbx
    push r12
    
    mov rbx, rdi
    
    xor eax, eax
.count_loop:
    movzx ecx, byte [rbx + rax]
    test cl, cl
    jz .count_done
    inc eax
    jmp .count_loop
.count_done:
    cmp eax, 1
    jle .return_fail
    
    mov r12d, eax
    xor eax, eax
    
.outer_loop:
    cmp eax, r12d
    jge .check_passed
    
    movzx edi, byte [rbx + rax]
    push rax
    call valid_char_failed
    pop rcx
    test eax, eax
    jnz .return_fail
    
    mov edx, ecx
    inc edx
.inner_loop:
    cmp edx, r12d
    jge .inner_done
    
    movzx esi, byte [rbx + rcx]
    movzx edi, byte [rbx + rdx]
    
    cmp esi, edi
    je .return_fail
    
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
    xor eax, eax
    jmp .exit
    
.return_fail:
    mov eax, 1
    
.exit:
    pop r12
    pop rbx
    leave
    ret

valid_char_failed:
    push rbp
    mov rbp, rsp
    push rbx
    
    mov bl, dil
    
    cmp bl, '+'
    je .return_fail
    cmp bl, '-'
    je .return_fail
    
    movzx edi, bl
    call ft_isspace
    test eax, eax
    jnz .return_fail
    
    cmp bl, 127
    je .return_fail
    
    xor eax, eax
    jmp .done
    
.return_fail:
    mov eax, 1
    
.done:
    pop rbx
    leave
    ret
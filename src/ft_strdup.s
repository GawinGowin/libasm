section .text
    global ft_strdup
    extern malloc
    extern ft_strlen
    extern ft_strcpy
    extern __errno_location

ft_strdup:
    push rbp
    mov rbp, rsp
    push rbx            ; save rbx (callee-saved)
    
    mov rbx, rdi        ; save original string pointer
    call ft_strlen      ; get string length
    inc rax             ; add 1 for null terminator
    
    mov rdi, rax        ; malloc(strlen + 1)
    call malloc wrt ..plt
    cmp rax, 0          ; check if malloc failed
    je .error           ; if NULL, handle error
    
    mov rdi, rax        ; dst = malloc result
    mov rsi, rbx        ; src = original string
    call ft_strcpy      ; strcpy(dst, src)
    
    pop rbx             ; restore rbx
    leave
    ret
    
.error:
    call __errno_location wrt ..plt
    mov dword [rax], 12 ; ENOMEM = 12
    mov rax, 0          ; return NULL
    pop rbx             ; restore rbx
    leave
    ret
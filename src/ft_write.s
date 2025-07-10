section .text
    global ft_write
    extern __errno_location

ft_write:
    push rbp
    mov rbp, rsp
    
    mov rax, 1          ; syscall number for write
    ; rdi = fd (already set)
    ; rsi = buf (already set)
    ; rdx = count (already set)
    syscall
    
    cmp rax, 0          ; check if return value is negative
    jl .error           ; if negative, handle error
    
    leave
    ret
    
.error:
    neg rax             ; make error code positive
    push rax            ; save error code
    call __errno_location wrt ..plt
    pop rdx             ; restore error code
    mov [rax], rdx      ; set errno
    mov rax, -1         ; return -1
    leave
    ret
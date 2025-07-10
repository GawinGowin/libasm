section .text
    global ft_strcpy

ft_strcpy:
    push rbp
    mov rbp, rsp
    
    mov rax, rdi        ; save dst for return value
    mov rcx, 0          ; counter = 0
    
.loop:
    mov dl, [rsi + rcx]         ; load src[i]
    mov [rdi + rcx], dl         ; dst[i] = src[i]
    cmp dl, 0                   ; check if src[i] == '\0'
    je .done                    ; if yes, exit loop
    inc rcx                     ; counter++
    jmp .loop                   ; continue loop
    
.done:
    leave
    ret
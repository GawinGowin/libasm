section .text
    global ft_strlen

ft_strlen:
    push rbp
    mov rbp, rsp
    
    mov rax, 0          ; counter = 0
    
.loop:
    cmp byte [rdi + rax], 0    ; check if str[i] == '\0'
    je .done                   ; if yes, exit loop
    inc rax                    ; counter++
    jmp .loop                  ; continue loop
    
.done:
    leave
    ret
section .text
    global ft_strcmp

ft_strcmp:
    push rbp
    mov rbp, rsp
    
    mov rcx, 0          ; counter = 0
    
.loop:
    mov al, [rdi + rcx]         ; load s1[i]
    mov dl, [rsi + rcx]         ; load s2[i]
    cmp al, dl                  ; compare s1[i] and s2[i]
    jne .diff                   ; if different, return difference
    cmp al, 0                   ; check if s1[i] == '\0'
    je .equal                   ; if yes, strings are equal
    inc rcx                     ; counter++
    jmp .loop                   ; continue loop
    
.diff:
    movzx rax, al               ; zero-extend s1[i] to rax
    movzx rdx, dl               ; zero-extend s2[i] to rdx
    sub rax, rdx                ; return s1[i] - s2[i]
    jmp .done
    
.equal:
    mov rax, 0                  ; return 0
    
.done:
    leave
    ret
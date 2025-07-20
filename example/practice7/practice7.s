section .text
  global safe_divide
  extern __errno_location

safe_divide:
  enter 0, 0                  ; set up stack frame
  
  cmp rsi, 0                  ; check if divisor is zero
  je .error                   ; if zero, jump to error handler
  
  mov rax, rdi                ; dividend to rax
  cqo                         ; sign extend rax to rdx:rax
  idiv rsi                    ; signed division: rax = rax / rsi
  
  leave
  ret

.error:
  push rax                    ; preserve registers
  call __errno_location wrt ..plt
  mov qword [rax], 22         ; set errno to EINVAL (22)
  pop rax
  mov rax, -1                 ; return error value
  leave
  ret

section .note.GNU-stack noalloc noexec nowrite progbits

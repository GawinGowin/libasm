section .text
  global ft_strdup
  extern ft_strlen
  extern ft_strcpy
  extern malloc
  extern __errno_location

ft_strdup:
  enter 0, 0
  push rbx            ; callee-saved

  mov rbx, rdi
  call ft_strlen
  mov rdi, rax
  add rdi, 1
  call malloc wrt ..plt
  cmp rax, 0
  je .error

  mov rdi, rax
  mov rsi, rbx
  call ft_strcpy
  
  pop rbx             ; restore rbx
  leave
  ret

.error:
  call __errno_location wrt ..plt
  mov dword [rax], 12 ; ENOMEM = 12
  mov rax, 0
  pop rbx             ; restore rbx
  leave
  ret

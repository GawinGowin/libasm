section .text
  global ft_read
  extern __errno_location

ft_read:
  enter 0, 0
  mov rax, 0
  syscall

  cmp rax, 0
  jl .error

  leave
  ret

.error:
  neg rax
  push rax
  call __errno_location wrt ..plt
  pop rdx
  mov [rax], rdx
  mov rax, -1
  leave
  ret
section .text
  global ft_isspace

ft_isspace:
  enter 0, 0
  cmp rdi, 9
  je .is_space
  cmp rdi, 10
  je .is_space
  cmp rdi, 11
  je .is_space
  cmp rdi, 12
  je .is_space
  cmp rdi, 13
  je .is_space
  cmp rdi, 32
  je .is_space
  mov eax, 0
  jmp .end

.is_space:
  mov eax, 1

.end:
  leave
  ret

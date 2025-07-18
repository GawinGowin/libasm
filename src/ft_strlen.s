section .text
  global ft_strlen

ft_strlen:
  mov rcx, -1
  mov al, 0
  cld
  repne scasb
  not rcx
  dec rcx
  mov rax, rcx
  ret
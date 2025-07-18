section .text
  global ft_strlen

ft_strlen:
  ; rdi points to the string
  mov rax, 0

.loop:
  cmp byte [rdi + rax], 0
  je .done
  inc rax
  jmp .loop

.done:
  ret
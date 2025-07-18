section .text
  global fibonacci

fibonacci:
  cmp rdi, 2
  jl .base_case

  push rbx
  push rdi
  dec rdi
  call fibonacci
  mov rbx, rax

  pop rdi
  sub rdi, 2
  call fibonacci
  add rax, rbx
  pop rbx
  ret

.base_case:
  mov rax, rdi
  ret

section .note.GNU-stack noalloc noexec nowrite progbits
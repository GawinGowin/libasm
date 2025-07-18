section .text
  global factorial

factorial:
  cmp rdi, 1
  jle .base_case

  push rdi
  dec rdi
  call factorial
  pop rdi
  mul rdi
  ret

.base_case:
  mov rax, 1
  ret

section .note.GNU-stack noalloc noexec nowrite progbits
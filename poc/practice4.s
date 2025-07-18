section .text
  global sum_six_numbers

sum_six_numbers:
  mov rax, rdi
  add rax, rsi
  add rax, rdx
  add rax, rcx
  add rax, r8
  add rax, r9
  ret

section .note.GNU-stack noalloc noexec nowrite progbits

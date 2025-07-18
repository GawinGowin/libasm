section .text
    global my_memcpy

my_memcpy:
  mov rax, rdi
  mov rcx, rdx

  cld
  rep movsb
  ret

section .note.GNU-stack noalloc noexec nowrite progbits

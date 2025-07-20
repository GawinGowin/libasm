section .text
  global ft_strcmp

ft_strcmp:
  mov rcx, 0

.loop: 
  mov al, [rdi + rcx]
  mov bl, [rsi + rcx]

  cmp al, bl
  jne .not_equal

  cmp al, 0
  je .done

  inc rcx
  jmp .loop

.done:
  mov rax, 0
  ret

.not_equal:
  movzx rax, al
  movzx rbx, bl
  sub rax, rbx
  ret

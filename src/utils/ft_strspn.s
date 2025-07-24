section .text
  global ft_strspn

ft_strspn:
  enter 0, 0
  push rbx
  push rcx
  push rdx
  mov rbx, 0
  
.loop:
  mov al, [rdi + rbx]
  test al, al
  jz .done
  
  mov rcx, rsi
  
.inner_loop:
  mov dl, [rcx]
  test dl, dl
  jz .done
  cmp al, dl
  je .found

  inc rcx
  jmp .inner_loop
  
.found:
  inc rbx 
  jmp .loop

.done:
  mov rax, rbx
  pop rdx
  pop rcx
  pop rbx
  leave
  ret

section .text
  global ft_strchr

ft_strchr:
  enter 0, 0
  push rbx
  
  mov rbx, rdi                  ; save string pointer
  movzx edx, sil                ; extend c to 32-bit (clear upper bits)
  
.loop:
  mov al, [rbx]                 ; load current character
  cmp al, dl                    ; compare with search character
  je .found                     ; if match, return current position
  
  test al, al                   ; check if current char is '\0'
  jz .not_found                 ; if end of string, character not found
  
  inc rbx                       ; move to next character
  jmp .loop
  
.found:
  mov rax, rbx                  ; return pointer to found character
  jmp .done
  
.not_found:
  cmp dl, 0                     ; check if searching for '\0'
  je .found                     ; if yes, return pointer to '\0'
  mov rax, 0                    ; else return NULL
  
.done:
  pop rbx
  leave
  ret
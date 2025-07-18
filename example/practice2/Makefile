NAME = a.out

ASM_OBJ = practice2.o
C_SRC = practice2.c

NASM = nasm
NASMFLAGS = -f elf64
CC = gcc
CFLAGS = -no-pie

.PHONY: all
all: $(NAME)

$(NAME): $(ASM_OBJ)
	$(CC) $(CFLAGS) $(ASM_OBJ) $(C_SRC) -o $(NAME)

$(ASM_OBJ): practice2.s
	$(NASM) $(NASMFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -f $(ASM_OBJ)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re: fclean all
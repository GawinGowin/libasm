NAME = a.out

SRCDIR = .
SRCS = practice1.s
OBJS = $(SRCS:.s=.o)

NASM = nasm
NASMFLAGS = -f elf64
LD = ld

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS)
	$(LD) $(OBJS) -o $(NAME)

%.o: %.s
	$(NASM) $(NASMFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJS)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re: fclean all
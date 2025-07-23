NAME = libasm.a

BUILD_DIR = ./build

SRCDIR = src
SRCS :=

SRCS += ft_strlen.s
SRCS += ft_strcpy.s
SRCS += ft_strcmp.s
SRCS += ft_write.s
SRCS += ft_read.s
SRCS += ft_strdup.s

B_SRCS :=
B_SRCS += ft_atoi_base.s

OBJS := $(addprefix $(SRCDIR)/, $(SRCS:.s=.o))
B_OBJS := $(addprefix $(SRCDIR)/, $(B_SRCS:.s=.o))

NASM = nasm
NASMFLAGS = -f elf64 -g -F dwarf
AR = ar
ARFLAGS = rcs
BONUS_KEEP = .bonus_keep

.PHONY: all
all:  $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

%.o: %.s
	$(NASM) $(NASMFLAGS) $< -o $@

.PHONY: bonus
bonus: $(BONUS_KEEP)

$(BONUS_KEEP): $(NAME) $(B_OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(B_OBJS)
	touch $(BONUS_KEEP)

%_bonus.o: %_bonus.s
	$(NASM) $(NASMFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJS) $(B_OBJS) $(BONUS_KEEP)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)
	rm -rf $(BUILD_DIR)

.PHONY: re
re: fclean all

.PHONY: build
build:
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake -DCMAKE_VERBOSE_MAKEFILE=ON ..  && make

.PHONY: test
test: build
	cd $(BUILD_DIR)/tests && make test
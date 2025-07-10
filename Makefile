NAME = libasm.a
TEST = test_libasm

BUILD_DIR = ./build

SRCDIR = src
SRCS :=

SRCS += ft_strlen.s
SRCS += ft_strcpy.s
SRCS += ft_strcmp.s
SRCS += ft_write.s
SRCS += ft_read.s
SRCS += ft_strdup.s

OBJS := $(addprefix $(SRCDIR)/, $(SRCS:.s=.o))

NASM = nasm
NASMFLAGS = -f elf64
AR = ar
ARFLAGS = rcs

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

%.o: %.s
	$(NASM) $(NASMFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJS)

.PHONY: fclean
fclean: clean
	rm -f $(NAME) $(TEST)

.PHONY: re
re: fclean all

.PHONY: build
build:
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake -DCMAKE_VERBOSE_MAKEFILE=ON ..  && make

.PHONY: test
test: build
	cd $(BUILD_DIR)/tests && make test
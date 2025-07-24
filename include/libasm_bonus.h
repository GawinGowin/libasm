#ifndef LIBASM_BONUS_H
#define LIBASM_BONUS_H

#include <stddef.h>
#include <sys/types.h>

int ft_atoi_base(const char *str, const char *base) __THROW __attribute_pure__ __nonnull((1, 2));

int ft_isspace(int c);

size_t ft_strspn(const char *__s, const char *__accept) __THROW __attribute_pure__
    __nonnull((1, 2));

char *ft_strchr(const char *__s, int __c) __THROW __attribute_pure__ __nonnull((1));

#endif /* LIBASM_BONUS_H */

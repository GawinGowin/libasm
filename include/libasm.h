#ifndef LIBASM_H
#define LIBASM_H

#include <stddef.h>
#include <sys/types.h>

size_t ft_strlen(const char *s) __THROW __attribute_pure__ __nonnull((1));

char *ft_strcpy(char *dst, const char *src) __THROW __nonnull((1, 2));

int ft_strcmp(const char *s1, const char *s2) __THROW __attribute_pure__ __nonnull((1, 2));

ssize_t ft_write(int fd, const void *buf, size_t count) __wur __attr_access((__read_only__, 2, 3));

ssize_t ft_read(int fd, void *buf, size_t count) __wur
    __fortified_attr_access(__write_only__, 2, 3);

char *ft_strdup(const char *__s) __THROW __attribute_malloc__ __nonnull((1));

#endif
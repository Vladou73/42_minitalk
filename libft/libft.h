#ifndef LIBFT_H
# define LIBFT_H

// necessary libraries.
# include <stdlib.h>
# include <unistd.h>
// libraries for testing functions
# include <stdio.h>
# include <ctype.h>
# include <string.h>

// prototypes
size_t ft_strlen(const char *s);
size_t ft_strlcpy(char *dst, char *src, size_t dst_size);
int   ft_atoi(const char *src);
void  *ft_memset(void *ptr, int c, size_t n);
void  ft_putchar_fd(char c, int fd);
void  ft_putstr_fd(char *s, int fd);
void  ft_putnbr_fd(int n, int fd);
void  ft_free_null_ptr(char **ptr);
char  *ft_strjoin_free(char **s1, char c);

#endif

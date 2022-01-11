#include "libft.h"

char  *ft_strjoin_free(char **s1, char c)
{
  char  *dst;
  size_t dst_size;

  if (!*s1 && !c)
    return (NULL);
  dst_size = ft_strlen(*s1) + 2;
  dst = malloc(sizeof(char) * dst_size);
  if (!dst)
    return (NULL);
  ft_memset(dst, 0, sizeof(char) * dst_size);
  ft_strlcpy(dst, *s1, dst_size);
  dst[ft_strlen(dst) + 1] = 0;
  dst[ft_strlen(dst)] = c;
  ft_free_null_ptr(s1);
  return (dst);
}
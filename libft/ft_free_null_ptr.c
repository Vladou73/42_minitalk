#include "libft.h"

void  ft_free_null_ptr(char **ptr)
{
  if (*ptr)
  {
    free(*ptr);
    *ptr = NULL;
  }
}
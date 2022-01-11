#include "libft.h"

int ft_atoi(const char *src)
{
  int dest;
  int sign;

  dest = 0;
  sign = 1;
  while (*src && (*src == ' ' || *src == '\r' || *src == '\v'
      || *src == '\t' || *src == '\f' || *src == '\n'))
    src++;
  if (*src == '-' || *src == '+')
  {
    if (*src == '-')
      sign = -1;
    src++;
  }
  while (*src && *src >= 48 && *src <= 57)
  {
    dest = dest * 10 + *src - 48;
    src++;
  }
  return (sign * dest);
}

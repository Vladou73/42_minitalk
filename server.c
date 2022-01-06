#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

#include "libc.h"

void	ft_free_null_ptr(char **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

size_t	ft_strlen(const char *s)
{
	size_t	i;
	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, char *src, size_t dst_size)
{
	size_t	i;
	size_t	src_size;

	src_size = ft_strlen(src);
	if (dst_size == 0)
		return (src_size);
	i = 0;
	while (i < dst_size - 1 && i < src_size)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_size);
}

char	*ft_strjoin_free(char **s1, char c)
{
	char	*dst;
	size_t	dst_size;
	size_t	i;

	if (!*s1 && !c)
		return (NULL);
	dst_size = ft_strlen(*s1) + 1 + 1;
	dst = malloc(sizeof(char) * dst_size);
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, *s1, dst_size);
	i = ft_strlen(dst);
	dst[i] = c;
	if (i != dst_size)
		dst[i + 1] = 0;
	ft_free_null_ptr(s1);
	return (dst);
}

//explanations converting binary to decimal
// https://www.youtube.com/watch?v=jEgiZQLNfiE&ab_channel=PortfolioCourses
char	convert_binary_to_char(char *bin_str)
{
	int	i;
	int	decimal_val;
	int	total;

	total = 0;
	decimal_val = 1;
	i = 7;
	while(i >= 0)
	{
		if (bin_str[i] == '1')
			total += decimal_val;
		decimal_val *= 2;
		i--;

	}
	return (char)(total);
}

//void	handler_sigusr(int	sigtype)
//{
//	static	char binary_str[7];
//	//static	char *msg;
//	int		bin_index;

//	//usleep(100);
//	bin_index = ft_strlen(binary_str);
//	if (sigtype == 30)
//		binary_str[bin_index] = '1';
//	else
//		binary_str[bin_index] = '0';

//	if (bin_index < 7)
//	{
//		binary_str[bin_index + 1] = 0;
//		//printf("lolz\n");
//	}
//	else //1) ajouter le binaire transformé en lettre à la variable msg puis 2) reset l'index du binary
//	{
//		//printf("coucou");
//		//msg = ft_strjoin_free(&msg, convert_binary_to_char(binary_str));
//		printf("%c", convert_binary_to_char(binary_str));
//		binary_str[0] = 0;
//	}
//	//printf("index=%d, bin=%s\n", bin_index, binary_str);
//}
//static void	ft_stock_char(int signal, siginfo_t *siginfo, void *data)
void handler_sigusr(int sig)
{
	printf("%d", sig);
}

int main()
{
	int	i;
	struct	sigaction sa;

	//memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_handler = handler_sigusr;
	sa.sa_flags = SA_SIGINFO;
	// sa.sa_mask

	i = getpid();
	printf("pid=%d\n", i);

	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();

	return (0);
}

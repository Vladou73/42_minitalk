#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

static char *msg;

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

void	*ft_memset(void *ptr, int c, size_t n)
{
	unsigned int	i;
	char			*s;

	i = 0;
	s = (char *) ptr;
	while (i < n)
	{
		s[i] = (unsigned char) c;
		i++;
	}
	return (ptr);
}

void	ft_free_null_ptr(char **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}


void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	len = ft_strlen(s);
	write(fd, s, len);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		n *= -1;
		ft_putchar_fd('-', fd);
	}
	if (n / 10 > 0)
		ft_putnbr_fd(n / 10, fd);
	ft_putchar_fd(n % 10 + '0', fd);
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

void	handler_sigusr(int sigtype, siginfo_t *siginfo, void *ucontext)
{
	static	char binary_str[7];
	int		bin_index;

	(void)ucontext;
	usleep(100);
	bin_index = ft_strlen(binary_str);
	if (sigtype == SIGUSR1)
		binary_str[bin_index] = '1';
	else
		binary_str[bin_index] = '0';
	if (bin_index < 7)
		binary_str[bin_index + 1] = 0;
	else
	{
		binary_str[0] = 0;
		msg = ft_strjoin_free(&msg, convert_binary_to_char(binary_str));
		if (convert_binary_to_char(binary_str) == '\0')
			ft_putstr_fd(msg, 1);
	}
	ft_putnbr_fd(1, siginfo->si_pid);
	kill(siginfo->si_pid, SIGUSR1);
}

int main()
{
	struct sigaction sa;

	ft_memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_sigaction = handler_sigusr;
	sa.sa_flags = SA_SIGINFO;
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);

	while (1)
		pause();
	return (0);
}

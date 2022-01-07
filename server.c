#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

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

void	handler_sigusr(int sigtype, siginfo_t *siginfo, void *data)
{
	static	char binary_str[7];
	int		bin_index;

	//usleep(100);
	bin_index = ft_strlen(binary_str);
	if (sigtype == 10)
		binary_str[bin_index] = '1';
	else
		binary_str[bin_index] = '0';

	if (bin_index < 7)
		binary_str[bin_index + 1] = 0;
	else //1) ajouter le binaire transformé en lettre à la variable msg puis 2) reset l'index du binary
	{
		ft_putchar_fd(convert_binary_to_char(binary_str), 1);
		binary_str[0] = 0;
		ft_putchar_fd(binary_str[0], 1);
		// usleep(1000);
	}
}

int main()
{
	struct sigaction sa;

	ft_memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_sigaction = handler_sigusr;
	sa.sa_flags = SA_SIGINFO;

	// sa.sa_flags = 0;
	// sigemptyset(&sa.sa_mask);
	// sa.sa_mask

	printf("pid=%d\n", getpid());

	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}

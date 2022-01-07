#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

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

int	ft_atoi(const char *src)
{
	int	dest;
	int	sign;

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

void	ft_send_signal(int pid, char c)
{
	int mask = 128; /* 10000000 */
	while (mask > 0)
	{
		if ((c & mask) > 0)
			kill(pid, SIGUSR1); //signal for bit 1
		else
			kill(pid, SIGUSR2); //signal for bit 0
		mask >>= 1; /* move the bit down */
		pause();
		// usleep(100);
	}
}

void	ft_handler_pingpong(int sigtype, siginfo_t *siginfo, void *ucontext)
{
	usleep(10);
}

int main(int argc, char **argv)
{
	char	*msg;
	int		pid;
	struct sigaction sa_client;

	if (argc < 3)
		return (1);

	ft_memset(&sa_client, 0, sizeof(struct sigaction));
	sa_client.sa_sigaction = ft_handler_pingpong;
	sa_client.sa_flags = SA_SIGINFO;

	pid = ft_atoi(argv[1]);
	msg = argv[2];
	// printf("%d\n",pid);

	sigaction(SIGUSR1, &sa_client, NULL);

	while (*msg)
	{
		ft_send_signal(pid, *msg);
		msg++;
		// usleep(100);
		// break;
	}
	ft_send_signal(pid, '\0');
	return (0);
}

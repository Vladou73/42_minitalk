#include <unistd.h>
#include <stdio.h>
#include <signal.h>

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
	// kill(pid, SIGUSR2);
	// printf("%c\n", c);
	// printf("%d", (c & mask) > 0 );
	int mask = 128; /* 10000000 */
	while (mask > 0)
	{
		// printf("%d", (c & mask) > 0 );
		if ((c & mask) > 0)
		{
			kill(pid, SIGUSR1); //signal for bit 1
			printf("1");
		}
		else
		{
			kill(pid, SIGUSR2); //signal for bit 0
			printf("0");
		}
		mask >>= 1; /* move the bit down */
		usleep(1000);
	}
}

int main(int argc, char **argv)
{
	int		i;
	char	*msg;
	int		pid;

	if (argc < 3)
		return (1);

	pid = ft_atoi(argv[1]);
	msg = argv[2];
	while (*msg)
	{
		ft_send_signal(pid, *msg);
		msg++;
		usleep(1000);
		break;
	}
	printf("\n");
	// kill(pid, SIGUSR1);
	return (0);
}

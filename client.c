#include "./includes/client.h"
#include <stdint.h>


void  ft_send_signal(int pid, char c)
{
	int mask = 128; /* 10000000 */
	while (mask > 0)
	{
		if ((c & mask) > 0)
			kill(pid, SIGUSR1); //signal for bit 1
		else
			kill(pid, SIGUSR2); //signal for bit 0
		mask >>= 1; /* move the bit down */
		//pause(); //uniquement si on utilise le ping pong
		usleep(1000); //need this usleep otherwise for large messages all signals are not sent
	}
}

//static void ft_handler_pingpong(int sigtype, siginfo_t *siginfo, void *ucontext)
//{
//	(void)sigtype;
//	(void)siginfo;
//	(void)ucontext;
//	usleep(10);
//}

int main(int argc, char **argv)
{
	char	*msg;
	int		pid;
	int		i;
	//struct sigaction sa_client; //uniquement si on utilise le ping pong
	uint32_t	len_msg;
	//int32_t	len_msg;

	if (argc < 3)
		return (1);

	pid = ft_atoi(argv[1]);
	msg = argv[2];
	len_msg = (uint32_t)ft_strlen(msg);

	printf("len_msg=%u\n",len_msg);
	printf("sizeof('0')=%lu\n",sizeof('\0'));
	printf("sizeof(int)*8=%lu\n", sizeof(int)*8);

	//ft_memset(&sa_client, 0, sizeof(struct sigaction));
	//sa_client.sa_sigaction = ft_handler_pingpong;
	//sa_client.sa_flags = SA_SIGINFO;
	//  sigaction(SIGUSR1, &sa_client, NULL);
	
	//start by sending 32 signals which represents the length of the message in 32 bits. 
	//this way server knows the length of the message and mallocs only once
	i = 31;
	while (i >= 0)
	{
		if ((len_msg & (1u << i)))
		{
			ft_putchar_fd('1',1);
			kill(pid, SIGUSR1); //signal for bit 1
		}	
		else
		{
			ft_putchar_fd('0',1);
			kill(pid, SIGUSR2); //signal for bit 0
		}	
		i--;
		//pause(); //uniquement si on utilise le ping pong
		usleep(1000); //need this usleep otherwise for large messages all signals are not sent
	}

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

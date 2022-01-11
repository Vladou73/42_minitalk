#include "./includes/server.h"

static char *msg;

static	int handle_msg_size(int sigtype, uint32_t count_signals, int bin_index, char is_first_signal)
{
	static	uint32_t len_msg;
	
	ft_putstr_fd("check", 1);
	if (is_first_signal == '\0')
	{
		bin_index = 31;
		is_first_signal = '1';
	}
	len_msg |= (uint32_t)((sigtype == SIGUSR1) << bin_index);
	bin_index--;
	count_signals++;
	if (bin_index == 0)
	{
		is_first_signal = '\0';
		//allocate full size of message
		msg = malloc(len_msg + 4); // + 4 pour le caractere NULL a la fin ?
		if (!msg)
			return (1);
		ft_memset(msg, 0, len_msg + 4);
	}
	return (0);
}

static void handler_sigusr_bis(int sigtype, siginfo_t *siginfo, void *ucontext)
{
	static	char c;
	static	int bin_index;
	static	char is_first_signal;
	static	uint32_t count_signals;

	(void)ucontext;
	(void)siginfo;
	usleep(100);

	//kill(siginfo->si_pid, SIGUSR1); //systeme ping pong -> pas sur de l'utiliser
	
	if (count_signals < 32)
		handle_msg_size(sigtype, count_signals, bin_index, is_first_signal);

	if (is_first_signal == '\0')
	{
		bin_index = 7;
		is_first_signal = '1';
	}
	if (bin_index >= 0)
	{
		c |= (char)((sigtype == SIGUSR1) << bin_index);
		bin_index--;
	}
	if (bin_index < 0)
	{
		//msg = ft_strjoin_free(&msg, c);
		msg[ft_strlen(msg)] = c;
		is_first_signal = '\0';
	if (c == '\0')
	{
		ft_putstr_fd(msg, 1);
		ft_free_null_ptr(&msg);
	}
	c = 0;
	}
}

int main()
{
  struct sigaction sa;

  ft_memset(&sa, 0, sizeof(struct sigaction));
  // sa.sa_sigaction = handler_sigusr;
  sa.sa_sigaction = handler_sigusr_bis;
  sa.sa_flags = SA_SIGINFO;
  ft_putnbr_fd(getpid(), 1);
  ft_putchar_fd('\n', 1);
  sigaction(SIGUSR1, &sa, NULL);
  sigaction(SIGUSR2, &sa, NULL);

  while (1)
    pause();
  return (0);
}
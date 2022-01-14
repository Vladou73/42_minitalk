/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 19:12:09 by vnafissi          #+#    #+#             */
/*   Updated: 2022/01/14 12:27:26 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/server.h"

static char	*g_msg;

static int	handle_msg_size(
	int sigtype, uint32_t *count_signals, char *is_first_signal
)
{
	static uint32_t	len_msg;

	if (*is_first_signal == '\0')
		*is_first_signal = '1';
	len_msg |= (uint32_t)((sigtype == SIGUSR1) << (31 - *count_signals));
	(*count_signals)++;
	if (*count_signals == 32)
	{
		*is_first_signal = '\0';
		g_msg = malloc(sizeof(char) * (len_msg + 1));
		if (!g_msg)
			return (1);
		ft_memset(g_msg, 0, sizeof(char) * (len_msg + 1));
	}
	return (0);
}

static void	print_reset_msg(
	char c, uint32_t *count_signals, char *is_first_signal, int	*bin_index
)
{
	g_msg[ft_strlen(g_msg)] = c;
	*is_first_signal = '\0';
	if (c == '\0')
	{
		ft_putstr_fd(g_msg, 1);
		ft_free_null_ptr(&g_msg);
		*count_signals = 0;
		*bin_index = 0;
	}
}

static void	store_print_msg(
	int sigtype, uint32_t *count_signals, char *is_first_signal
)
{
	static int	bin_index;
	static char	c;

	if (*is_first_signal == '\0')
	{
		bin_index = 7;
		*is_first_signal = '1';
	}
	if (bin_index >= 0)
	{
		c |= (char)((sigtype == SIGUSR1) << bin_index);
		bin_index--;
	}
	if (bin_index < 0)
	{
		print_reset_msg(c, count_signals, is_first_signal, &bin_index);
		c = 0;
	}
}

static void	handler_sigusr(int sigtype, siginfo_t *siginfo, void *ucontext)
{
	static char		is_first_signal;
	static uint32_t	count_signals;

	(void)ucontext;
	(void)siginfo;
	usleep(100);
	if (count_signals < 32)
		handle_msg_size(sigtype, &count_signals, &is_first_signal);
	else
		store_print_msg(sigtype, &count_signals, &is_first_signal);
}

int	main(void)
{
	struct sigaction	sa;

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

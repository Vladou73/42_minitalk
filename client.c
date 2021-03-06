/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 19:02:14 by vnafissi          #+#    #+#             */
/*   Updated: 2022/01/14 14:48:03 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/client.h"

static void	ft_send_signal(int pid, char c)
{
	int	mask;

	mask = 128;
	while (mask > 0)
	{
		if ((c & mask) > 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		mask >>= 1;
		usleep(1000);
	}
}

static void	ft_send_signal_len(int pid, int i, uint32_t len_msg)
{
	if ((len_msg & (1u << i)))
		kill(pid, SIGUSR1);
	else
		kill(pid, SIGUSR2);
	usleep(1000);
}

static int	has_wrong_params(int argc, char **argv)
{
	if (argc != 3)
	{
		ft_putstr_fd("wrong number of params.", 1);
		return (1);
	}
	if (kill(ft_atoi(argv[1]), 0) == -1)
	{
		ft_putstr_fd("wrong pid passed in params", 1);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	char		*msg;
	int			pid;
	int			i;
	uint32_t	len_msg;

	if (has_wrong_params(argc, argv) == 1)
		return (1);
	pid = ft_atoi(argv[1]);
	msg = argv[2];
	len_msg = (uint32_t)ft_strlen(msg);
	i = 31;
	while (i >= 0)
	{
		ft_send_signal_len(pid, i, len_msg);
		i--;
	}
	while (*msg)
	{
		ft_send_signal(pid, *msg);
		msg++;
	}
	ft_send_signal(pid, '\0');
	return (0);
}

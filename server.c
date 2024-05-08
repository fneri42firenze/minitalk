/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filippo <filippo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 00:29:08 by filippo           #+#    #+#             */
/*   Updated: 2024/05/08 03:07:50 by filippo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	conv_bin_to_char(int signumber, char *character)
{
	if (signumber == SIGUSR1)
		*character = (*character << 1) | 1;
	else if (signumber == SIGUSR2)
		*character = *character << 1;
}

void	sig_handler_server(int signumber, siginfo_t *info, void *context)
{
	static int		byte = 0;
	static char		character = 0;
	static int		pid = 0;

	(void)context;
	if (pid == 0)
		pid = info->si_pid;
	conv_bin_to_char(signumber, &character);
	if (byte == 7)
	{
		byte = 0;
		if (!character)
		{
			ft_putchar_fd('\n', 1);
			kill(pid, SIGUSR1);
			pid = 0;
			return ;
		}
		ft_putchar_fd(character, 1);
		character = 0;
	}
	else
		byte++;
	kill(pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	sig;

	ft_putendl_fd("Server PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = SA_RESTART | SA_SIGINFO;
	sig.sa_sigaction = sig_handler_server;
	ft_putendl_fd("Server is waiting for messages...", 1);
	ft_putchar_fd('\n', 1);
	if ((sigaction(SIGUSR1, &sig, NULL) == -1)
		|| (sigaction(SIGUSR2, &sig, NULL) == -1))
	{
		ft_putendl_fd("Error: sigaction failed", 1);
		return (1);
	}
	while (1)
		pause();
	return (0);
}

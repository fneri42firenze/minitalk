/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fneri <fneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 00:29:11 by filippo           #+#    #+#             */
/*   Updated: 2024/05/21 15:26:33 by fneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_recived;

void	sig_handler_client(int signum, siginfo_t *info, void *context)
{
	static int		byte;

	(void)context;
	(void)info;
	(void)signum;
	g_recived = 1;
	if (signum == SIGUSR1)
		ft_putendl_fd("Message correctly received by the server!", 1);
	else if (signum == SIGUSR2)
	{
		byte++;
	}
}

int	conv_char_to_bin(char character, int pid)
{
	int		i;
	int		byte;

	byte = 7;
	while (byte >= 0)
	{
		i = 0;
		if ((character >> byte) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (g_recived == 0)
		{
			if (i == 50)
			{
				ft_putendl_fd("Error: timeout, no responses from server", 1);
				exit (1);
			}
			i++;
			usleep(1);
		}
		g_recived = 0;
		byte--;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	struct sigaction	sig;
	int					byte;
	int					pid;

	byte = 0;
	pid = ft_atoi(argv[1]);
	if (argc != 3 || pid <= 0)
	{
		ft_putendl_fd(" INVALID PID or USAGE,use: ./server PID MESSAGE", 1);
		return (1);
	}
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = SA_RESTART | SA_SIGINFO;
	sig.sa_sigaction = sig_handler_client;
	if (sigaction(SIGUSR1, &sig, NULL) == -1
		|| sigaction(SIGUSR2, &sig, NULL) == -1)
		ft_putstr_fd("Error: sigaction failed", 1);
	while (argv[2][byte])
	{
		conv_char_to_bin(argv[2][byte++], pid);
	}
	conv_char_to_bin('\0', pid);
	return (0);
}

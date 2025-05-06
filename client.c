/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcardoso <jcardoso@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:28:18 by jcardoso          #+#    #+#             */
/*   Updated: 2025/05/06 14:29:40 by jcardoso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_talk.h"

volatile sig_atomic_t	g_ack = 0;

void	ack_handler(int sig)
{
	(void)sig;
	g_ack = 1;
}

void	send_bit(int c, int pid)
{
	int	i;

	i = 8;
	while (--i >= 0)
	{
		g_ack = 0;
		if ((c >> i) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		while (!g_ack)
			pause();
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	int					i;
	int					server_pid;

	i = -1;
	if (argc != 3)
		return (1);
	sa.sa_handler = ack_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	server_pid = ft_atoi(argv[1]);
	while (argv[2][++i])
		send_bit(argv[2][i], server_pid);
	return (0);
}

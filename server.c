/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcardoso <jcardoso@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:09:43 by jcardoso          #+#    #+#             */
/*   Updated: 2025/05/06 14:27:29 by jcardoso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_talk.h"

void	bit_receiver(int sig, siginfo_t *info, void *context)
{
	static char	c = 0;
	static int	i = 0;

	(void) context;
	if (sig == SIGUSR1)
		c = (c << 1);
	else if (sig == SIGUSR2)
		c = (c << 1) | 1;
	i++;
	if (i == 8)
	{
		write(1, &c, 1);
		i = 0;
		c = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	pid_t				pid;
	int					i;
	char				*s;
	struct sigaction	sa;

	pid = getpid();
	s = ft_itoa(pid);
	sa.sa_sigaction = bit_receiver;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	i = -1;
	while (s[++i])
	{
		write(1, &s[i], 1);
	}
	while (1)
		pause();
	return (0);
}

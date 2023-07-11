/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groman-l <groman-l@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:02:44 by groman-l          #+#    #+#             */
/*   Updated: 2023/07/11 16:52:56 by groman-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

void	handler(int sig)
{
	static int				bite = 0;
	static unsigned char	ch = '\0';

	ch <<= 1;
	if (sig == SIGUSR1)
		ch |= 1;
	bite++;
	if (bite == 8)
	{
		if ((int)ch <= 128)
			ft_printf("%c", ch);
		else if ((int)ch >= 128)
			ft_printf("%c", ch);
		bite = 0;
		if (ch == '\0')
			ft_printf("\n");
		ch = '\0';
	}
}

void	confirm(void)
{
	if (signal(SIGUSR1, handler) == SIG_ERR)
		exit(EXIT_FAILURE);
	if (signal(SIGUSR2, handler) == SIG_ERR)
		exit(EXIT_FAILURE);
}

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	if (!pid)
		ft_printf("NO PID");
	else
		ft_printf("PID: %i\n", pid);
	confirm();
	while (TRUE)
		sleep(1);
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groman-l <groman-l@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:14:18 by groman-l          #+#    #+#             */
/*   Updated: 2023/07/11 15:18:21 by groman-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

int	msg_error(int e, int exit_)
{
	e == E_FA && ft_printf("client: Too few arguments");
	e == E_MA && ft_printf("client: Too many arguments");
	e == E_KL && ft_printf("client: No connection with server");
	return (exit_);
}

void	send_sig(int pid, int sig)
{
	if (kill(pid, sig) == ERROR)
		exit (msg_error(E_KL, EXIT_FAILURE));
	if (usleep(100) == ERROR)
		exit (msg_error(E_US, EXIT_FAILURE));
}

void	turn_bin(const int pid, char ch, int bite)
{
	while (bite >= 0)
	{
		if (((ch >> bite) & 1) == 1)
			send_sig(pid, SIGUSR1);
		else
			send_sig(pid, SIGUSR2);
		bite--;
		if (usleep(200) == ERROR)
			exit (msg_error(E_US, EXIT_FAILURE));
	}
}

int	main(int ac, char **av)
{
	pid_t	pid;
	int		i;

	i = -1;
	if (ac <= 2)
		return (msg_error(E_FA, ERROR));
	if (ac >= 4)
		return (msg_error(E_MA, ERROR));
	pid = ft_atoi(av[1]);
	while (av[2][++i])
		turn_bin(pid, av[2][i], 7);
	turn_bin(pid, '\0', 7);
	return (SUCCESS);
}

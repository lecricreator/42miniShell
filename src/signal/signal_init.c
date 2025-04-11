/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:52:33 by lomorale          #+#    #+#             */
/*   Updated: 2025/04/11 21:43:13 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test(int sigtype)
{
	t_data *data;
	if (sigtype == SIGINT)
	{
		data = recover_data_address(NULL);
		if (data->pid)
		{
			kill(data->pid, SIGINT);
			ft_printf_fd(1, "\n");
		}
		else
			ft_printf_fd(1,"\nMinishell $ ");
	}
	else if (sigtype == SIGQUIT)
	{
		// //ft_printf_fd(1,"Minishell $ ");
		//rl_on_new_line();
		// rl_replace_line("", 0);
		// rl_redisplay();
		// write(STDOUT_FILENO, "  ", 2);
		// // ft_printf_fd(1, "Ctrl + \\\n");
		return ;
	}
}

void	sig_init()
{
	struct sigaction sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = &test;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

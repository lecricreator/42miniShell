/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singnal_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:52:33 by lomorale          #+#    #+#             */
/*   Updated: 2025/04/11 10:59:54 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test(int sigtype)
{
	if (sigtype == SIGINT)
		{
			ft_putstr(1, "\n");
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
			//exit_status = 130;
		}
	else if (sigtype == SIGQUIT)
	{
		rl_redisplay();
		ft_printf_fd(1, "Ctrl + \\\n");
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

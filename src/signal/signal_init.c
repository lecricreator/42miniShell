/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:52:33 by lomorale          #+#    #+#             */
/*   Updated: 2025/04/22 15:31:28 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handle(int sigtype, siginfo_t *info, void *uncont)
{
	t_data	*data;

	(void)info;
	(void)uncont;
	data = recover_data_address(NULL);
	if (sigtype == SIGINT)
	{
		if (data->pid)
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			data->pid = 0;
		}
		else
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}

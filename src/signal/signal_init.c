/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:52:33 by lomorale          #+#    #+#             */
/*   Updated: 2025/04/22 11:27:31 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
void disable_echoctl(void)
{
	struct termios term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
	{
		perror("tcgetattr");
		return;
	}

	// Clear the ECHOCTL flag to disable the echoing of control characters.
	term.c_lflag &= ~ECHOCTL;

	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
	{
		perror("tcsetattr");
		return;
	}
}
*/
void	sig_handle(int sigtype, siginfo_t *info, void *uncont)
{
	(void)info;
	(void)uncont;
	t_data *data;

	data = recover_data_address(NULL);
	if (sigtype == SIGINT)
	{
		if(data->pid)
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
	// else if (sigtype == SIGQUIT)
	// {
	// 	// rl_replace_line(rl_line_buffer, 0);
	// 	// rl_on_new_line();
	// 	// rl_redisplay();
	// }
}

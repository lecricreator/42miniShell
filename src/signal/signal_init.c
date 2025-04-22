/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:52:33 by lomorale          #+#    #+#             */
/*   Updated: 2025/04/22 02:12:57 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	test(int sigtype)
{

	if (sigtype == SIGINT)
	{
			ft_printf_fd(1, "\n^C\n");
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
	}
	else if (sigtype == SIGQUIT)
	{
		rl_replace_line(rl_line_buffer, 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sig_init(void)
{
	struct sigaction sa;

	disable_echoctl();
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = &test;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

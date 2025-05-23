/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_and_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:07:16 by lomorale          #+#    #+#             */
/*   Updated: 2025/05/23 15:09:15 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_status(int status, int exit_code)
{
	int	child_exit;

	child_exit = WEXITSTATUS(status);
	if (child_exit != 0)
		exit_code = child_exit;
	else
		exit_code = 0;
	return (exit_code);
}

void	wait_and_status(t_data *data)
{
	int	exit_code;
	int	sig;

	exit_code = data->status;
	if (data->n_fork && data->pid)
	{
		waitpid(data->pid, &data->status, 0);
		if (WIFEXITED(data->status))
			exit_code = change_status(data->status, exit_code);
		else if (WIFSIGNALED(data->status))
		{
			sig = WTERMSIG(data->status);
			if (sig == SIGQUIT)
				ft_printf_fd(2, "Quit (core dumped)\n");
			exit_code = 128 + sig;
		}
	}
	while (data->n_fork-- > 0)
		waitpid(-1, NULL, 0);
	data->status = exit_code;
}

// void	wait_and_status(t_data *data)
// {
// 	int	exit_code;
// 	int	child_exit;
// 	int	sig;

// 	exit_code = data->status;
// 	while (data->n_fork--)
// 	{
// 		waitpid(-1, &data->status, 0);
// 		if (WIFEXITED(data->status))
// 		{
// 			child_exit = WEXITSTATUS(data->status);
// 			if (child_exit != 0)
// 				exit_code = child_exit;
// 		}
// 		else if (WIFSIGNALED(data->status))
// 		{
// 			sig = WTERMSIG(data->status);
// 			if (sig == SIGQUIT)
// 				ft_printf_fd(2, "Quit (core dumped)\n");
// 			exit_code = 128 + sig;
// 		}
// 	}
// 	data->status = exit_code;
// }

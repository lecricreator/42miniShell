/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in_exit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:41:24 by lomorale          #+#    #+#             */
/*   Updated: 2025/04/26 10:42:44 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_exit(int exit_status, char *args)
{
	tmp_data = recover_data_address(NULL);
	if (tmp_data->pid)
		ft_printf_fd(2, "exit\n");
	if (args && exit_status == 2)
		ft_printf_fd(2, "Minishell: exit: %s:  numeric argument required\n",
		args);
	free_data(tmp_data);
	exit(exit_status);
}

void	exec_exit(char **cmd_args)
{
	int		i;
	int		exit_status;
	t_data	*tmp_data;

	exit_status = EXIT_SUCCESS;
	if (cmd_args)
	{
		i = -1;
		if (cmd_args[1])
		{
			while (cmd_args[1][++i])
				if (!ft_isdigit(cmd_args[1][i]))
					break ;
			if (!cmd_args[1][i])
				exit_status = ft_atoi(cmd_args[1]);
			else
				exit_status = 2;
		}
	}
	free_exit(exit_status, cmd_args[1]);
}

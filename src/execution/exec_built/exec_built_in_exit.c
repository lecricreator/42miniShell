/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in_exit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:41:24 by lomorale          #+#    #+#             */
/*   Updated: 2025/04/24 12:31:42 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_exit(char **cmd_args)
{
	t_data	*tmp_data;
	int		i;
	int		exit_status;

	exit_status = EXIT_SUCCESS;
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
	ft_printf_fd(2, "exit\n");
	if (cmd_args[1] && exit_status == 2)
		ft_printf_fd(2, "Minishell: exit: %s:  numeric argument required\n",
				cmd_args[1]);
	tmp_data = recover_data_address(NULL);
	free_data(tmp_data);
	exit(exit_status);
}

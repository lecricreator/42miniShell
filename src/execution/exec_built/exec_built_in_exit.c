/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in_exit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:41:24 by lomorale          #+#    #+#             */
/*   Updated: 2025/05/14 21:57:13 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_exit_msg(int pid, int exit_status, char **args)
{
	if (!pid)
	 	ft_printf_fd(2, "exit\n");
	if (args && args[1] && exit_status == 2)
		ft_printf_fd(2, "Minishell: exit: %s: numeric argument required\n",
			args[1]);
}

static int	valid_exit_status(char *args)
{
	int	status;

	status = ft_atoi(args);
	if (status > 255 || status < 0)
		return (status % 256);
	return (status);
}

static int	valid_arg_syntax(char *arg)
{
	int	i;

	i = 0;
	if (!ft_isdigit(arg[i]) && arg[i] != '+' && arg[i] != '-')
		return (0);
	else if (arg[i] == '+' || arg[i] == '-')
		i++;
	if (ft_strlen(arg + i) > 19)
		return (0);
	while (arg[i] && ft_isdigit(arg[i]))
		i++;
	if (!arg[i])
		return (1);
	else
		return (0);
}

int	exec_exit(char **cmd_args)
{
	int		exit_status;
	t_data	*data;

	data = recover_data_address(NULL);
	exit_status = EXIT_SUCCESS;
	if (cmd_args)
	{
		if (cmd_args[1])
		{
			if (valid_arg_syntax(cmd_args[1]))
				exit_status = valid_exit_status(cmd_args[1]);
			else
				exit_status = 2;
		}
	}
	print_exit_msg(data->pid, exit_status, cmd_args);
	if (cmd_args && (count_table(cmd_args) > 2) && (exit_status != 2))
		return (error_handle(ERR_MANY_ARGS, "exit", NULL, CONTINUE));
	free_data(data);
	exit(exit_status);
}

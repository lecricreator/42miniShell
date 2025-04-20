/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 23:10:19 by lomorale          #+#    #+#             */
/*   Updated: 2025/04/20 17:43:24 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_cmd *cmd, t_list *env_list)
{
	if (cmd->type == BI_CD)
	{
		if (cmd->nbr_arg > 2)
		{
			error_handle(NULL, "cd", "too many arguments", 0);
			return (1);
		}
		return (exec_cd(cmd, &env_list));
	}
	if (cmd->type == BI_PWD)
		return (exec_pwd(), errno);
	if (cmd->type == BI_ECHO)
		return (exec_echo(cmd->cmd_args), errno);
	if (cmd->type == BI_EXIT)
		return (exec_exit(), errno);
	if (cmd->type == BI_ENV)
		return (print_env(env_list), errno);
	if (cmd->type == BI_EXPORT)
	{
		exec_export(cmd->cmd_args, &env_list);
		return (errno);
	}
	if (cmd->type == BI_UNSET)
		return (exec_unset(cmd->cmd_args, &env_list), errno);
	return (errno);
}

void	exec_builtin_before_fork(t_data *data, t_cmd *cmd, t_fds *fds)
{
	if (cmd->is_pipe || fds->prev_pipe > 0)
	{
		data->pid = fork();
		if (data->pid == -1)
			error_handle(data, cmd->cmd_args[0],
				"execution:75:\nFork failed", 1);
		data->n_fork++;
		if (!data->pid)
		{
			exec_pipe(data, cmd, fds);
			exec_builtin(cmd, data->env_list);
			free_data(data);
			exit(errno);
		}
	}
	else
		exec_builtin(cmd, data->env_list);
}

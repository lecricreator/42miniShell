/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 01:32:13 by odruke-s          #+#    #+#             */
/*   Updated: 2025/04/04 01:48:06 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_if_absolute_path(t_cmd *cmd)
{
	errno = 0;
	cmd->command_path = ft_strdup(cmd->cmd_args[0]);
	if (!access(cmd->command_path, X_OK))
		return (0);
	else
		return (1);
}

void	find_program(t_data *data, t_cmd *cmd)
{
	int		i;

	i = 0;
	data->path = get_path(data->path, data->env_list);
	if (ft_strchr(cmd->cmd_args[0], '/'))
	{
		if (!cmd_if_absolute_path(cmd))
			return ;
		else
		{
			error_handle(data, cmd->cmd_args[0], "directory not found", 0);
			return ;
		}
	}
	while (data->path[i])
	{
		cmd->command_path = ft_strjoin(data->path[i], cmd->cmd_args[0]);
		if (!access(cmd->command_path, X_OK))
			return ;
		free(cmd->command_path);
		cmd->command_path = NULL;
		i++;
	}
	error_handle(data,
		cmd->cmd_args[0], "command not found", 0);
}

int	handle_procesess(t_data *data, t_cmd *cmd, t_fds *fds, char **env_tab)
{
	errno = 0;
	if (!cmd->cmd_args[0])
		error_handle(data, "", "permission denied", 1);
	else if (!cmd->command_path)
	{
		free_data(data);
		exit(127);
	}
	exec_redir(data, cmd->redir, fds);
	exec_pipe(data, cmd, fds);
	if (execve(cmd->command_path, cmd->cmd_args, env_tab) == -1)
	{
		free_table(env_tab);
		error_handle(data, cmd->cmd_args[0], strerror(errno), 1);
	}
	return (0);
}

void	exec_cmd(t_data *data, t_cmd *cmd, t_fds *fds)
{
	char	**env_tab;

	env_tab = get_env_tab(data->env_list);
	find_program(data, cmd);
	data->pid = fork();
	if (data->pid == -1)
		error_handle(data, "", "Error:\nFork failed", 1);
	data->n_fork++;
	if (!data->pid)
		handle_procesess(data, cmd, fds, env_tab);
	if (env_tab)
		free_table(env_tab);
}

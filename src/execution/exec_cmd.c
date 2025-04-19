/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 01:32:13 by odruke-s          #+#    #+#             */
/*   Updated: 2025/04/18 16:27:57 by lomorale         ###   ########.fr       */
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

int	verif_access(char **path, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (path[i])
	{
		cmd->command_path = ft_strjoin(path[i], cmd->cmd_args[0]);
		if (!access(cmd->command_path, X_OK))
		{
			free(path);
			return (1);
		}
		free(cmd->command_path);
		cmd->command_path = NULL;
		i++;
	}
	return (0);
}

int	find_program(t_data *data, t_cmd *cmd)
{
	char	**path;

	path = NULL;
	path = get_path(path, data->env_list);
	if (ft_strchr(cmd->cmd_args[0], '/'))
	{
		if (!cmd_if_absolute_path(cmd))
		{
			return (free(path), 0);
		}
		else
		{
			return (free(path), error_handle(data, cmd->cmd_args[0],
					"directory not found", 0));
		}
	}
	if (path)
		if (verif_access(path, cmd))
			return (0);
	if (!path)
		return (free(path), error_handle(data,
				cmd->cmd_args[0], "No such file or directory", 0));
	return (free(path), error_handle_without_rl(data,
			cmd->cmd_args[0], "command not found", 0));
}

int	handle_procesess(t_data *data, t_cmd *cmd, t_fds *fds, char **env_tab)
{
	(void)fds;
	errno = 0;
	if (!cmd->cmd_args[0])
		error_handle(data, "", "permission denied", 1);
	else if (!cmd->command_path)
	{
		free_data(data);
		exit(127);
	}
	//exec_redir(data, cmd->redir, fds);
	exec_pipe(data, cmd, fds);
	if (execve(cmd->command_path, cmd->cmd_args, env_tab) == -1)
	{
		free_table(env_tab);
		error_handle(data, cmd->cmd_args[0], strerror(errno), 1);
	}
	return (0);
}

void	exec_cmd(t_data *data, t_cmd *cmd, t_fds *fds, char **tmp_var)
{
	char	**env_tab;

	if (find_program(data, cmd))
		return ;
	env_tab = get_env_tab(data->env_list, tmp_var);
	data->pid = fork();
	if (data->pid == -1)
		error_handle(data, "", "Error:\nFork failed", 1);
	data->n_fork++;
	if (!data->pid)
		handle_procesess(data, cmd, fds, env_tab);
	if (env_tab)
		free_table(env_tab);
	if (tmp_var)
		free_table(tmp_var);
}

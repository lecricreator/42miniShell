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

t_list	*exec_pipe(t_data *data, t_list *token_list, t_fds *fds)
{
	if (dup2(fds->pipefd[0], fds->prev_pipe) == -1)// Redirect pipe[0] as standard input
		error_handle(data, "pipefd[0]", "Error:\ndup2 failed", 1);
	close(fds->pipefd[0]);
		error_handle(data, "std in", "Error:\ndup2 failed", 1);
	close(fds->std_in);
	return (token_list->next);
}

t_list	*exec_redir(t_data *data, t_list *token_list, t_fds *fds)
{
	close(fds->pipefd[0]);
	if (dup2(fds->pipefd[1], STDOUT_FILENO) == -1)
		error_handle(data, (char *)((t_token *)token_list->content)->str, "File: execution_utils || Function: exec_pipe || dup2 failed", 1);
	/*command*/
	return (token_list->next);
}

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

int	handle_procesess(t_data *data, t_cmd *cmd, char **env_tab)
{
	errno = 0;
	if (!cmd->cmd_args[0])
		error_handle(data, "", "permission denied", 1);
	else if (!cmd->command_path)
	{
		free_data(data);
		exit(127);
	}
//	else if (fds->prev_pipe < 1)
//	{
//		free_data(data);
//		exit(0);
//	}
//	close(fds->pipefd[0]);
//	if (dup2(fds->prev_pipe, STDIN_FILENO) == -1)
//		error_handle(data, "prev_pipe", "in child: \ndup2 failed", 1);
//	if (dup2(fds->pipefd[1], STDOUT_FILENO) == -1)
//		error_handle(data, "pipefd[1]", "in child:\ndup2 failed", 1);
//	close(fds->prev_pipe);
//	close(fds->pipefd[1]);
	if (execve(cmd->command_path, cmd->cmd_args, env_tab) == -1)
	{
		free_table(env_tab);
		error_handle(data, cmd->cmd_args[0], strerror(errno), 1);
	}
	return (0);
}

void	exec_cmd(t_data *data, t_cmd *cmd)
{
	char	**env_tab;

	env_tab = get_env_tab(data->env_list);
	find_program(data, cmd);
	data->pid = fork();
	if (data->pid == -1)
		error_handle(data, "", "Error:\nFork failed", 1);
	if (!data->pid)
		handle_procesess(data, cmd, env_tab);
	if (env_tab)
		free_table(env_tab);
}

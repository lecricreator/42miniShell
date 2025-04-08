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

void	exec_pipe(t_data *data, t_cmd *cmd, t_fds *fds)
{
	if (cmd->is_pipe)
	{
		close(fds->pipefd[0]);
		if (dup2(fds->pipefd[1], STDOUT_FILENO) == -1)
			error_handle(data, cmd->cmd_args[0], "execution_utils.c:87:\ndup2 failed", 1);
		close(fds->pipefd[1]);
	}
	if (fds->prev_pipe > 0)
	{
		if (dup2(fds->prev_pipe, STDIN_FILENO) == -1)
			error_handle(data, cmd->cmd_args[0], "execution_utils.c:87:\ndup2 failed", 1);
		close(fds->prev_pipe);
	}
}

void	change_io(t_data *data, t_redir *redir, t_fds *fds)
{
	if (redir->type == OP_REDIR_OUT || redir->type == OP_APPEND)
	{
		fds->std_out = dup(STDOUT_FILENO);
		if (redir->type == OP_REDIR_OUT)
			fds->outfile = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);// check shell convention for permissions
		else
			fds->outfile = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fds->outfile < 0)
			error_handle(data, redir->filename, strerror(errno), 1);
		dup2(fds->outfile, STDOUT_FILENO);
		if (fds->outfile < 0)
			error_handle(data, redir->filename, strerror(errno), 1);
	}
	if (redir->type == OP_REDIR_IN)
	{
		fds->std_in = dup(STDIN_FILENO);
		fds->infile = open(redir->filename, O_RDONLY);
		if (fds->infile < 0)
			error_handle(data, redir->filename, strerror(errno), 1);
		dup2(fds->infile, STDIN_FILENO);
		if (fds->infile < 0)
			error_handle(data, redir->filename, strerror(errno), 1);
		close(fds->infile);
	}
}

void	exec_redir(t_data *data, t_list *redir, t_fds *fds)
{
	t_redir *tmp_redir;
	t_list	*tmp_head;

	if (redir)
		tmp_redir = (t_redir *)redir->content;
	tmp_head = 	redir;
	while (tmp_head)
	{
		change_io(data, tmp_redir, fds);
		tmp_head = tmp_head->next;
		if (tmp_head)
			tmp_redir = (t_redir *)tmp_head->content;
	}
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

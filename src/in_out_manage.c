/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_manage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 23:54:39 by odruke-s          #+#    #+#             */
/*   Updated: 2025/04/08 23:55:11 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_io(t_data *data, t_fds *fds)
{
	if (fds->outfile != -1)
	{
		dup2(fds->std_out, STDOUT_FILENO);
		if (fds->std_out < 0)
			error_handle(data, "std out", "execution.c:108:\ndup2 failed", 1);
		close(fds->std_out);
		close(fds->outfile);
	}
	if (fds->infile != -1)
	{
		dup2(fds->std_in, STDIN_FILENO);
		if (fds->std_in < 0)
			error_handle(data, "std in", "execution.c:116:\ndup2 failed", 1);
		close(fds->std_in);
		close(fds->infile);
	}
}

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

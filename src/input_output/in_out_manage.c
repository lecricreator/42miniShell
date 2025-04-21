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

void	reset_io(t_fds *fds)
{
	if (fds->outfile != -1 || fds->std_out != -1)
	{
		dup2(fds->std_out, STDOUT_FILENO);
		if (fds->std_out < 0)
			error_handle(ERR_UNKNOWN, "std out",
				"in_out_manage.c:21\ndup2 failed", KILL);
		if (fds->std_out > -1)
			close(fds->std_out);
		if (fds->outfile > -1)
			close(fds->outfile);
		fds->std_out = -1;
		fds->outfile = -1;
	}
	if (fds->infile != -1 || fds->std_in != -1)
	{
		dup2(fds->std_in, STDIN_FILENO);
		if (fds->std_in < 0)
			error_handle(ERR_UNKNOWN, "std in",
				"in_out_management.c:\ndup2 failed", KILL);
		if (fds->std_in > -1)
			close(fds->std_in);
		if (fds->infile > -1)
			close(fds->infile);
		fds->std_in = -1;
		fds->infile = -1;
	}
}

void	exec_pipe(t_cmd *cmd, t_fds *fds)
{
	if (cmd->is_pipe)
	{
		if (STDOUT_FILENO != 1)
		{
			cmd->is_pipe = 0;
			return ;
		}
		close(fds->pipefd[0]);
		if (dup2(fds->pipefd[1], STDOUT_FILENO) == -1)
			error_handle(ERR_UNKNOWN, cmd->cmd_args[0],
				"in_out_manage.c:56:\ndup2 failed", KILL);
		close(fds->pipefd[1]);
	}
	if (fds->prev_pipe > 0)
	{
		if (dup2(fds->prev_pipe, STDIN_FILENO) == -1)
			error_handle(ERR_UNKNOWN, cmd->cmd_args[0],
				"in_out_manage.c:63:\ndup2 failed", KILL);
		close(fds->prev_pipe);
	}
}

void	change_io(t_redir *redir, t_fds *fds)
{
	if (redir->type == OP_REDIR_OUT || redir->type == OP_APPEND)
	{
		fds->std_out = dup(STDOUT_FILENO);
		if (redir->type == OP_REDIR_OUT)
			fds->outfile = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);// check shell convention for permissions
		else
			fds->outfile = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fds->outfile < 0)
			error_handle(ERR_NO_FILE, redir->filename, NULL, CONTINUE);
		dup2(fds->outfile, STDOUT_FILENO);
		if (fds->outfile < 0)
			error_handle(ERR_NO_FILE, redir->filename, NULL, CONTINUE);
	}
	if (redir->type == OP_REDIR_IN)
	{
		if (STDIN_FILENO != 0)
			return ;
		fds->std_in = dup(STDIN_FILENO);
		fds->infile = open(redir->filename, O_RDONLY);
		if (fds->infile < 0)
		{
			error_handle(ERR_NO_FILE, redir->filename, NULL, CONTINUE);
			return ;
		}
		dup2(fds->infile, STDIN_FILENO);
		if (fds->infile < 0)
		{
			error_handle(ERR_NO_FILE, redir->filename, NULL, CONTINUE);
			return ;
		}
		close(fds->infile);
	}
}

void	exec_redir(t_list *redir, t_fds *fds)
{
	t_redir *tmp_redir;
	t_list	*tmp_head;

	tmp_head = redir;
	if (tmp_head)
		tmp_redir = (t_redir *)tmp_head->content;
	while (tmp_head)
	{
		change_io(tmp_redir, fds);
		tmp_head = tmp_head->next;
		if (tmp_head)
			tmp_redir = (t_redir *)tmp_head->content;
	}
}

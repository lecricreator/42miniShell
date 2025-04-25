/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_manage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 23:54:39 by odruke-s          #+#    #+#             */
/*   Updated: 2025/04/25 23:34:53 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_io(t_fds *fds)
{
	if (!fds)
		return ;
	restore_stdin(fds);
	restore_stdout(fds);
	if (fds->herepipe[0] != -1)
	{
		fds->herepipe[0] = -1;
		fds->herepipe[1] = -1;
	}
}

void	exec_pipe(t_cmd *cmd, t_fds *fds)
{
	if (cmd->is_pipe)
	{
		if (fds->outfile != -1)
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

int	change_redir_in(t_redir *redir, t_fds *fds)
{
	if (redir->type == OP_REDIR_IN)
	{
		fds->infile = open(redir->filename, O_RDONLY);
		if (fds->infile < 0)
			return (error_handle(ERR_NO_FILE, redir->filename, NULL, CONTINUE));
		dup2(fds->infile, STDIN_FILENO);
		if (fds->infile < 0)
			return (error_handle(ERR_NO_FILE, redir->filename, NULL, CONTINUE));
		close(fds->infile);
	}
	return (0);
}

int	change_io(t_redir *redir, t_fds *fds)
{
	int	exit_code;

	if (redir->type == OP_REDIR_OUT || redir->type == OP_APPEND)
	{
		if (redir->type == OP_REDIR_OUT)
			fds->outfile = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC,
					0644);
		else
			fds->outfile = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND,
					0644);
		if (fds->outfile < 0)
			return (error_handle(ERR_PERMISSION, redir->filename, NULL,
					CONTINUE));
		dup2(fds->outfile, STDOUT_FILENO);
		if (fds->outfile < 0)
			error_handle(ERR_NO_FILE, redir->filename, NULL, CONTINUE);
	}
	exit_code = change_redir_in(redir, fds);
	return (exit_code);
}

int	exec_redir(t_list *redir, t_fds *fds)
{
	t_redir	*tmp_redir;
	t_list	*tmp_head;

	tmp_head = redir;
	if (tmp_head)
		tmp_redir = (t_redir *)tmp_head->content;
	while (tmp_head)
	{
		if (change_io(tmp_redir, fds))
			return (1);
		tmp_head = tmp_head->next;
		if (tmp_head)
			tmp_redir = (t_redir *)tmp_head->content;
	}
	return (0);
}

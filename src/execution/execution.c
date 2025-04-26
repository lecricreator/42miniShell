/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 02:07:30 by odruke-s          #+#    #+#             */
/*   Updated: 2025/04/26 10:27:42 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_fds(t_data *data)
{
	data->fds = (t_fds *)malloc(sizeof(t_fds));
	data->fds->infile = -1;
	data->fds->outfile = -1;
	data->fds->pipefd[0] = -1;
	data->fds->pipefd[1] = -1;
	data->fds->herepipe[0] = -1;
	data->fds->herepipe[1] = -1;
	data->fds->prev_pipe = -1;
	data->fds->std_out = dup(STDOUT_FILENO);
	data->fds->std_in = dup(STDIN_FILENO);
}

static void	check_heredoc(t_list *redir, t_fds *fds)
{
	t_list	*tmp_head;
	t_redir	*tmp_redir;

	tmp_head = redir;
	if (tmp_head)
		tmp_redir = ((t_redir *)(tmp_head)->content);
	while (tmp_head)
	{
		if (tmp_redir->type == OP_HEREDOC)
		{
			exec_heredoc(tmp_redir, fds);
			break ;
		}
		tmp_head = tmp_head->next;
		if (tmp_head)
			tmp_redir = ((t_redir *)(tmp_head)->content);
	}
}

static void	handle_fds(t_cmd **tmp_cmd, t_fds *fds)
{
	if ((*fds).prev_pipe != -1)
	{
		close((*fds).prev_pipe);
		(*fds).prev_pipe = -1;
	}
	if ((*tmp_cmd)->is_pipe)
	{
		close((*fds).pipefd[1]);
		(*fds).prev_pipe = dup((*fds).pipefd[0]);
		close((*fds).pipefd[0]);
	}
}

void	find_to_execute(t_data *data, char **tmp_var, t_cmd **tmp_cmd,
		t_fds *fds)
{
	if ((*tmp_cmd)->is_pipe)
	{
		if (pipe((*fds).pipefd) == -1)
			error_handle(ERR_UNKNOWN, (*tmp_cmd)->cmd_args[0],
				"execution.c:73\nPipe failed", KILL);
	}
	check_heredoc((*tmp_cmd)->redir, fds);
	if (!exec_redir((*tmp_cmd)->redir, fds))
	{
		if (is_builtin((*tmp_cmd)->type))
		{
			(*tmp_cmd)->nbr_arg = count_table((*tmp_cmd)->cmd_args);
			exec_builtin_before_fork(data, (*tmp_cmd), fds);
		}
		else if ((*tmp_cmd)->type == COMMAND)
			exec_cmd(data, (*tmp_cmd), fds, tmp_var);
	}
	handle_fds(tmp_cmd, fds);
}

void	execution(t_data *data)
{
	t_cmd	*tmp_cmd;
	t_list	*tmp_head;
	char	**tmp_var;

	if (!data->cmd_list)
		return ;
	init_fds(data);
	tmp_var = NULL;
	tmp_head = data->cmd_list;
	while (tmp_head)
	{
		tmp_cmd = (t_cmd *)tmp_head->content;
		if (is_var_declaration(tmp_cmd->type, 0))
		{
			tmp_var = create_var(data, tmp_cmd);
			tmp_head = tmp_head->next;
			continue ;
		}
		find_to_execute(data, tmp_var, &tmp_cmd, data->fds);
		tmp_head = tmp_head->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 02:07:30 by odruke-s          #+#    #+#             */
/*   Updated: 2025/04/11 18:49:10 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exec_builtin(t_cmd *cmd, t_list *env_list)
{
	if (cmd->type == BI_CD)
	{
		if (cmd->nbr_arg <= 1)
			chdir(give_var_env_list("HOME", env_list));
		else if (cmd->nbr_arg <= 2)
			exec_cd(cmd->cmd_args[1], &env_list);
		else
			ft_printf_fd(2, "Minishell: cd: too many arguments\n");//we should use the error funtion, it will display the same msg
		return (errno);
	}
	if (cmd->type == BI_PWD)
	{
		exec_pwd();
		return (errno);
	}
	if (cmd->type == BI_ECHO)
	{
		exec_echo(cmd->cmd_args);
		return(errno);
	}
	if (cmd->type == BI_EXIT)
	{
		exec_exit();
		return (errno);
	}
	if (cmd->type == BI_ENV)
	{
		print_env(env_list);
		return (errno);
	}
	if (cmd->type == BI_EXPORT)
	{
		if (cmd->nbr_arg == 2)
			exec_export(cmd->cmd_args, &env_list);
		return (errno);
	}
	if (cmd->type == BI_UNSET)
	{
		exec_unset(cmd->cmd_args, &env_list);
		return (errno);
	}
	return (errno);
}

void	exec_builtin_before_fork(t_data * data, t_cmd *cmd, t_fds *fds)
{
	if (cmd->is_pipe || fds->prev_pipe > 0)
	{
		data->pid = fork();
		if (data->pid == -1)
			error_handle(data, cmd->cmd_args[0], "execution:75:\nFork failed", 1);
		data->n_fork++;
		if (!data->pid)
		{
			exec_redir(data, cmd->redir, fds);
			exec_pipe(data, cmd, fds);
			exec_builtin(cmd, data->env_list);
			free_data(data);
			exit(errno);
		}
	}
	else
	{
		exec_redir(data, cmd->redir, fds);
		exec_builtin(cmd, data->env_list);
	}
}

void	init_fds(t_fds *fds)
{
	fds->infile = -1;
	fds->outfile = -1;
	fds->pipefd[0] = -1;
	fds->pipefd[1] = -1;
	fds->herepipe[0] = -1;
	fds->herepipe[1] = -1;
	fds->prev_pipe = -1;
	fds->std_in = -1;
	fds->std_out = -1;
}

void	check_heredoc(t_data *data, t_list *redir, t_fds *fds)
{
	t_list	*tmp_head;
	t_redir	*tmp_redir;

	tmp_head = redir;
	if (tmp_head)
	tmp_redir = ((t_redir *)(tmp_head)->content);
	while(tmp_head)
	{
		if (tmp_redir->type == OP_HEREDOC)
		{
			exec_heredoc(data, tmp_redir, fds);
			break ;
		}
		tmp_head = tmp_head->next;
		if (tmp_head)
			tmp_redir = ((t_redir *)(tmp_head)->content);
	}
}

void	execution(t_data *data)
{
	t_cmd	*tmp_cmd;
	t_list	*tmp_head;
	t_fds	fds;
	char	**tmp_var;

	init_fds(&fds);
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
		if (tmp_cmd->is_pipe)
		{
			if (pipe(fds.pipefd) == -1)
				error_handle(data, tmp_cmd->cmd_args[0], "File: execution.c || Function: execution || Pipe failed", 1);
		}
		check_heredoc(data, tmp_cmd->redir, &fds);
		if (is_builtin(tmp_cmd->type))
		{
			tmp_cmd->nbr_arg = count_table(tmp_cmd->cmd_args);
			exec_builtin_before_fork(data, tmp_cmd, &fds);
		}
		else if (tmp_cmd->type == COMMAND)
			exec_cmd(data, tmp_cmd, &fds, tmp_var);
		if (tmp_cmd->is_pipe)
		{
			close(fds.pipefd[1]);
			fds.prev_pipe = dup(fds.pipefd[0]);
			close(fds.pipefd[0]);
		}
		if (fds.std_in != -1 || fds.std_out != -1)
			reset_io(data, &fds);
		tmp_head = tmp_head->next;
	}
}

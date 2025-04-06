/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 02:07:30 by odruke-s          #+#    #+#             */
/*   Updated: 2025/04/06 17:15:58 by lomorale         ###   ########.fr       */
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
			ft_printf_fd(2, "Minishell: cd: too many arguments\n");
		return (errno);
	}
	if (cmd->type == BI_PWD)
	{
		exec_pwd();
		return (errno);
	}
	if (cmd->type == BI_ECHO)
	{
		exec_echo(cmd->cmd_args, env_list);
		return(errno);
	}
	if (cmd->type == BI_PWD)
	{
		exec_pwd();
		return (errno);
	}
	/*
	if (tmp_token->type == BI_EXIT)
	{
		exec_exit();
		return (token_list->next);
	}
	*/
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
	/*
	if (tmp_token->type == BI_UNSET)
	{
		exec_unset();
		return (token_list->next);
	}
	*/
	return (errno);
}

void	redirect_in_out(t_data *data, t_fds *fds)
{
	if (fds->prev_pipe == -1)
	{
		fds->std_in = dup(STDIN_FILENO); // backup for stdin
		fds->std_out = dup(STDOUT_FILENO); //backup for stdout
		if (dup2(fds->pipefd[0], STDOUT_FILENO) == -1)
			error_handle(data, "pipe_fd[1]", "Error:\ndup2 failed", 1);
		close(fds->pipefd[0]);
	}
	else
	{
		if (dup2(fds->prev_pipe, STDIN_FILENO) == -1)
			error_handle(data, "prev_pipe", "Error:\ndup2 failed", 1);
	}
}

void	restore_in_out(t_data *data, t_fds *fds)
{
	if (!(fds->prev_pipe < 0))
		close(fds->prev_pipe);
	fds->prev_pipe = -1;
	if (dup2(fds->pipefd[1], STDIN_FILENO) == -1)  // Redirect pipe[0] as standard input
		error_handle(data, "pipefd[0]", "Error:\ndup2 failed", 1);
	if (dup2(fds->std_out, STDOUT_FILENO) == -1) // Restore standard output to terminal
		error_handle(data, "std out", "Error:\ndup2 failed", 1);
	close(fds->pipefd[1]);
	close(fds->std_out);
	if (dup2(fds->std_in, STDIN_FILENO) == -1) // Restore standard input to terminal
		error_handle(data, "std in", "Error:\ndup2 failed", 1);
	close(fds->std_in);
}

void	execution(t_data *data)
{
	t_cmd	*tmp_cmd;
	t_list	*tmp_head;
	t_fds	fds;

	tmp_head = data->cmd_list;
	fds.prev_pipe = -1;
	while (tmp_head)
	{
		tmp_cmd = (t_cmd *)tmp_head->content;
		if (pipe(fds.pipefd) == -1)
			error_handle(data, tmp_cmd->cmd_args[0], "File: execution.c || Function: execution || Pipe failed", 1);
		if (tmp_cmd->type <= 6)// built in commands
		{
			tmp_cmd->nbr_arg = count_table(tmp_cmd->cmd_args);
			exec_builtin(tmp_cmd, data->env_list);
		}
		else if (tmp_cmd->type == COMMAND)
			exec_cmd(data, tmp_cmd);
		tmp_head = tmp_head->next;
	}
}

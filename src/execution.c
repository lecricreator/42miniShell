/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 02:07:30 by odruke-s          #+#    #+#             */
/*   Updated: 2025/04/04 17:22:02 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exec_builtin(t_cmd *cmd, t_list *env_list)
{
	if (cmd->type == BI_CD)
	{
		exec_cd(cmd->cmd_args[1], env_list);
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
	/*
	if (tmp_token->type == BI_EXPORT)
	{
		exec_export();
		return (token_list->next);
	}
	if (tmp_token->type == BI_UNSET)
	{
		exec_unset();
		return (token_list->next);
	}
	if (tmp_token->type == BI_ECHO)
	{
		exec_echo(argument?);
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
		fds->prev_pipe = dup(STDIN_FILENO);
		close(fds->pipefd[0]);
	}
	else
	{
		if (dup2(fds->prev_pipe, STDIN_FILENO) == -1)
			error_handle(data, "prev_pipe", "Error:\ndup2 failed", 1);
	}
}

void	exec_builtin_before_fork(t_data * data, t_cmd *cmd, t_fds *fds)
{
	if (cmd->is_pipe || fds->prev_pipe > 0)
	{
		data->pid = fork();
		if (data->pid == -1)
			error_handle(data, cmd->cmd_args[0], "execution:96:\nFork failed", 1);
		data->n_fork++;
		if (!data->pid)
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
			exec_builtin(cmd, data->env_list);
			free_data(data);
			exit(errno);
		}
	}
	else
		exec_builtin(cmd, data->env_list);

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
	
		if (tmp_cmd->is_pipe)
		{
			if (pipe(fds.pipefd) == -1)
				error_handle(data, tmp_cmd->cmd_args[0], "File: execution.c || Function: execution || Pipe failed", 1);
				/*
			if (fds.prev_pipe == -1)
			{
			//	fds.std_in = dup(STDIN_FILENO); // backup for stdin
		//		fds.std_out = dup(STDOUT_FILENO); //backup for stdout
				//fds.prev_pipe = dup(STDIN_FILENO);
			}
		}
		else
		{
			if (fds.prev_pipe > 0)
			{
				if (dup2(fds.std_out, STDOUT_FILENO) == -1)
					error_handle(data, tmp_cmd->cmd_args[0], "execution_utils.c:87:\ndup2 failed", 1);
			*/
		}		
		if (tmp_cmd->type <= 6)// built in commands
			exec_builtin_before_fork(data, tmp_cmd, &fds);
		else if (tmp_cmd->type == COMMAND)
			exec_cmd(data, tmp_cmd, &fds);
		if (tmp_cmd->is_pipe)
		{
		//	close(fds.prev_pipe);
			close(fds.pipefd[1]);
			fds.prev_pipe = dup(fds.pipefd[0]);
			close(fds.pipefd[0]);
		}
	//	else
	//		close(fds.pipefd[0]);
		tmp_head = tmp_head->next;
	}
}

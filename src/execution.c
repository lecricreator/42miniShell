#include <minishell.h>

t_list  *exec_builtin(t_list *token_list, t_list *env_list)
{
	t_token *tmp_token;

	tmp_token = token_list->content;
	if (tmp_token->type == BI_CD)
	{
		token_list = token_list->next;
		tmp_token = token_list->content;
		exec_cd(tmp_token->str);
        if (errno)
            return (NULL);
		return (token_list->next);
	}
	if (tmp_token->type == BI_PWD)
	{
		exec_pwd();
        if (errno)
            return (NULL);
		return (token_list->next);
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
	if (tmp_token->type == BI_ENV)
	{
		print_env(env_list);
		return (token_list->next);
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
	return (token_list->next);
}

void	execution(t_data *data)
{
	t_token *tmp_token;
	t_list  *tmp_head;
    t_fds   fds;

	tmp_head = data->token_list;
	while (tmp_head)
	{
		tmp_token = (t_token *)data->token_list->content;
		if (pipe(fds.pipefd) == -1)
			handle_error(data, tmp_token->type , "File: execution.c || Function: execution || Pipe failed", 1);
		if (tmp_token->type <= 6)
        {
			tmp_head = exec_builtin(tmp_head, data->env_list);
            if (!tmp_head)
                error_handle(data, tmp_token->str, strerror(errno), 1);
        }
		else if (tmp_token->type == COMMAND)
			tmp_head =  exec_cmd(data, tmp_head, &fds);
		else if (tmp_token->type >= 8 && tmp_token->type <= 11)// redir tokens (< > >>) and << HEREDOC??
            tmp_head = exec_redir(data, tmp_head, &fds);
        else if (tmp_token->str == OP_PIPE)
            tmp_head = exec_pipe(data, tmp_head, &fds);
		else
			error_handle(data, tmp_token->str, "File: execution.c || Function: execution || unexpected behaviour", 1); //this case never could happen
	}
}

#include <minishell.h>

t_list  *exec_builtin(t_list *token_list, t_list *env_list)
{
    t_token *tmp_token;

    tmp_token = token_list->content;
	/*
    if (tmp_token->type == BI_CD)
	{
		exec_cd();//not finished
		return (token_list->next);
	}
	*/
    if (tmp_token->type == BI_PWD)
	{
		exec_pwd();
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

void    execution(t_data *data)
{
    t_token *tmp_token;
    t_list  *tmp_head;
//    t_type   state;

    tmp_head = data->token_list;
    while (tmp_head)
    {
        tmp_token = (t_token *)data->token_list->content;
        if (tmp_token->type <= 6)
            tmp_head = exec_builtin(tmp_head, data->env_list);
		/*
        else if (tmp_token->type == COMMAND)
            tmp_head =  exec_cmd(tmp_head);
        else if (tmp_token->type >= 8 && tmp_token->type <= 11)// redir tokens (< > >>) and << HEREDOC??
            tmp_head = exec_redir(tmp_head);
        else if (tmp_token->str == OP_PIPE)
            tmp_head = exec_pipe(tmp_head);
		*/
        else
           error_handle(data, tmp_token->str, "execution function failed on execution.c", 1); //this case never could happen
    }
}

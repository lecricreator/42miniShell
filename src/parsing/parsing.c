/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:26:38 by odruke-s          #+#    #+#             */
/*   Updated: 2025/04/17 10:48:11 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_type	check_env_var_type(t_token *next_token)
{
	if (!next_token)
		return (ENV_VAR);
	if (next_token->type == ENV_VAR)
		return (ENV_VAR);
	if (is_redir_op(next_token->type))
		return (FILENAME);
	if (is_any_cmd(next_token->type) || next_token->type == UNKNOW)
		return (TMP_VAR);
	if (next_token->type == OP_PIPE)
		return (COMMAND);
	return (ENV_VAR);

}

static t_type	token_zero(t_token *token, t_list *next_node)//re test this and correct if needed
{
	t_token *next_token;

	next_token = NULL;
	if (next_node)
		next_token = (t_token *)next_node->content;
	if (token->type <= 6)
		return (ARGUMENT);
	else if (token->type >= 8 && token->type <= 10)
		return (FILENAME);
	else if (token->type == OP_HEREDOC)
		return (DELIMITER);
	else if (token->type == OP_PIPE)
		return (BAD_TOKEN);
	else if (token->type == UNKNOW)
	{
		token->type = COMMAND;
		return (ARGUMENT);
	}
	else if (token->type == ENV_VAR)
	{
		token->type = check_env_var_type(next_token);
		return (COMMAND);
	}
	return (BAD_TOKEN);
}

static t_type	next_token(t_token *token, t_type state, t_type last)
{
	if (token->type >= 8 && token->type <= 10)
		return (FILENAME);
	if (token->type == OP_HEREDOC)
		return (DELIMITER);
	if (token->type == OP_PIPE)
		return (COMMAND);
	if (state == ARGUMENT)
	{
		token->type = ARGUMENT;
		return (ARGUMENT);
	}
	if (state == COMMAND)
	{
		if (token->type > 6)
			token->type = COMMAND;
		return (ARGUMENT);
	}
	if (state == FILENAME && (last == OP_REDIR_OUT || last == OP_APPEND))
	{
		token->type = FILENAME;
		return (ARGUMENT);
	}
	if (state == FILENAME && last == OP_REDIR_IN)
	{
		token->type = FILENAME;
		return (COMMAND);
	}
	if (state == DELIMITER)
	{
		token->type = DELIMITER;
		return (COMMAND);
	}
	if (token->type == ENV_VAR && last == TMP_VAR)
	{
		token->type = TMP_VAR;
		return (COMMAND);
	}
	else
		return (BAD_TOKEN);
}

void	parsing(t_data *data)
{
	t_token	*tmp_token;
	t_list	*tmp_head;
	t_type	state;
	t_type	last;

	lexing_tokens(data, &data->input);
	//(data->token_list);
	tmp_head = data->token_list;
	state = COMMAND;
	last = COMMAND;
	while (tmp_head)
	{
		tmp_token = (t_token *)tmp_head->content;
		if (tmp_token->index == 0)
			state = token_zero(tmp_token, tmp_head->next);
		else
			state = next_token(tmp_token, state, last);
		if (state == BAD_TOKEN)
		{
			error_handle(data, tmp_token->str, "syntax error near elemnt", 0);//modify error handle to output the correct error format
			return ;// handle this to return the program to the prompt
		}
		last = tmp_token->type;
		tmp_head = tmp_head->next;
	}
}

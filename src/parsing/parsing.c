/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:26:38 by odruke-s          #+#    #+#             */
/*   Updated: 2025/04/04 01:42:04 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_type	token_zero(t_token *token)//re test this and correct if needed
{
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
	else
		return (BAD_TOKEN);
}

void	check_env_var(t_data *data, t_token *token)
{
	char *tmp;

	if (token->type != ENV_VAR)
		return ;
	token->type = UNKNOW;
	if (!token->str[1])
		return ;
	tmp = token->str;
	token->str = ft_strdup(give_var_env_list(token->str + 1, data->env_list));
	if (!token->str)
		error_handle(data, "token->str", "parsing.c:83\nft_strdup failed", 1);
	free(tmp);

}

void	parsing(t_data *data)
{
	t_token	*tmp_token;
	t_list	*tmp_head;
	t_type	state;
	t_type	last;

	lexing_tokens(data, data->input);
//	print_token_list(data->token_list);
	tmp_head = data->token_list;
	state = COMMAND;
	last = COMMAND;
	while (tmp_head)
	{
		tmp_token = (t_token *)tmp_head->content;
		check_env_var(data, tmp_token);
		if (tmp_token->index == 0)
			state = token_zero(tmp_token);
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

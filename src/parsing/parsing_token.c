/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:10:35 by lomorale          #+#    #+#             */
/*   Updated: 2025/04/22 13:15:53 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_type	token_zero(t_token *token)
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
	else if (token->type == ENV_VAR)
	{
		token->type = COMMAND;
		return (ARGUMENT);
	}
	return (BAD_TOKEN);
}

static t_type	continue_next_token(t_token *token, t_type state, t_type last)
{
	if (state == FILENAME && (last == OP_REDIR_OUT || last == OP_APPEND))
		return (token->type = FILENAME, COMMAND);
	if (state == FILENAME && last == OP_REDIR_IN)
		return (token->type = FILENAME, COMMAND);
	if (state == DELIMITER)
		return (token->type = DELIMITER, COMMAND);
	if (token->type == ENV_VAR)
		return (token->type = state, state);
	else
		return (BAD_TOKEN);
}

t_type	next_token(t_token *token, t_type state, t_type last)
{
	if (token->type >= 8 && token->type <= 10)
	{
		if (state == FILENAME || state == DELIMITER)
			return (BAD_TOKEN);
		return (FILENAME);
	}
	if (token->type == OP_HEREDOC)
	{
		if (state == FILENAME || state == DELIMITER)
			return (BAD_TOKEN);
		return (DELIMITER);
	}
	if (token->type == OP_PIPE)
		return (COMMAND);
	if (state == ARGUMENT)
		return (token->type = ARGUMENT, ARGUMENT);
	if (state == COMMAND)
	{
		if (token->type > 6)
			token->type = COMMAND;
		return (ARGUMENT);
	}
	return (continue_next_token(token, state, last));
}

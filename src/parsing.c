/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:26:38 by odruke-s          #+#    #+#             */
/*   Updated: 2025/03/27 22:30:10 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_env(t_list **env_list, char **env)
{
	char	*tmp_content;
	int		i;

	i = 0;
	tmp_content = NULL;
	while (env[i])
	{
		tmp_content = ft_strdup(env[i]);
		if (!tmp_content)
			return ;
		ft_lstadd_back(env_list, ft_lstnew(tmp_content));
		i++;
	}
}

static t_type	token_zero(t_token *token)
{
	if (token->type < 8)
		return (ARGUMENT);
	else if (token->type == OP_REDIR_IN)
		return (FILENAME);
	else if (token->type == UNKNOW)
	{
		token->type = COMMAND;
		return (ARGUMENT);
	}
	return (BAD_TOKEN);
}

static t_type	next_token(t_token *token, t_type state)
{
	if (token->type >= 8 && token->type <= 11)// redir tokens (< > >>) and << HEREDOC??
		return (FILENAME);
	if (token->type == OP_PIPE)
	{
		if (token->index == 1)
			return (BAD_TOKEN);
		return (COMMAND);
	}
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
	if (state == FILENAME)
	{
		token->type = FILENAME;
		return (COMMAND);
	}
	else
		return (BAD_TOKEN);
}

void	parsing(t_data *data)
{
	t_token *tmp_token;
	t_list	*tmp_head;
	t_type	state;

	lexing_tokens(data, data->input);
	tmp_head = data->token_list;
	state = COMMAND;
	while (tmp_head)
	{
		tmp_token = (t_token *)tmp_head->content;
		if (tmp_token->index == 0)
			state = token_zero(tmp_token);
		else
			state = next_token(tmp_token, state);
		if (state == BAD_TOKEN)
		{
			ft_printf_fd(2, "invalid token\n");// manage this case
			return ;
		}
		tmp_head = tmp_head->next;
	}
}

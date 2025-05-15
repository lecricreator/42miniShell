/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:26:38 by odruke-s          #+#    #+#             */
/*   Updated: 2025/04/22 14:03:44 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_var_temp(t_list *token_list)
{
	t_token	*tmp_token;
	t_list	*tmp_head;

	tmp_head = token_list;
	tmp_token = (t_token *)tmp_head->content;
	while (tmp_head && tmp_token->type == ENV_VAR)
	{
		tmp_token->type = TMP_VAR;
		tmp_head = tmp_head->next;
		if (tmp_head)
			tmp_token = (t_token *)tmp_head->content;
	}
}

static int	is_bad_token(t_type type, t_token *token, t_list **token_list)
{
	if (type == BAD_TOKEN)
	{
		error_handle(ERR_SYNTAX, token->str, NULL, CONTINUE);
		free_list(token_list, free_token);
		token_list = NULL;
		return (1);
	}
	return (0);
}

int	parsing_start(t_data **data, t_list **tmp_head, t_token **tmp_token,
		int *i)
{
	*i = 0;
	*tmp_head = (*data)->token_list;
	if (!*tmp_head)
		return (1);
	*tmp_token = (t_token *)(*tmp_head)->content;
	if (is_bad_token((*tmp_token)->type, *tmp_token, &(*data)->token_list))
		return (1);
	while (*tmp_head && (*tmp_token)->type == ENV_VAR)
	{
		(*tmp_token)->index = 0;
		(*i)++;
		(*tmp_head) = (*tmp_head)->next;
		if ((*tmp_head))
			*tmp_token = (t_token *)(*tmp_head)->content;
	}
	if (*tmp_head)
	{
		(*tmp_token)->index -= (*i);
		make_var_temp((*data)->token_list);
	}
	return (0);
}

void	verify_state(t_type *state, t_token *tmp_token, t_data **data)
{
	if ((*state == FILENAME || *state == DELIMITER))
	{
		if (!tmp_token->index)
			error_handle(ERR_SYNTAX, "newline", NULL, CONTINUE);
		else
			error_handle(ERR_SYNTAX, tmp_token->str, NULL, CONTINUE);
		free_list(&(*data)->token_list, free_token);
		(*data)->token_list = NULL;
	}
}

void	parsing(t_data *data)
{
	t_pars	pars;
	int		i;

	lexing_tokens(data, &data->input);
//	print_token_list(data->token_list);
	pars.state = COMMAND;
	pars.last = COMMAND;
	if (parsing_start(&data, &pars.tmp_head, &pars.tmp_token, &i))
		return ;
	while (pars.tmp_head)
	{
		pars.tmp_token = (t_token *)pars.tmp_head->content;
		if (pars.tmp_token->index == 0)
			pars.state = token_zero(pars.tmp_token);
		else
		{
			pars.tmp_token->index -= i;
			pars.state = next_token(pars.tmp_token, pars.state, pars.last);
		}
		if (is_bad_token(pars.state, pars.tmp_token, &data->token_list))
			return ;
		pars.last = pars.tmp_token->type;
		pars.tmp_head = pars.tmp_head->next;
	}
	verify_state(&pars.state, pars.tmp_token, &data);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:31:14 by odruke-s          #+#    #+#             */
/*   Updated: 2025/04/26 10:33:21 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_exp_synt(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	else
		return (0);
}

void	check_for_expansion(t_data *data, char **input)
{
	t_mini_expan	*ex;

	init_mini_expand(&ex);
	while ((*input)[ex->i])
	{
		ex->quotes = is_in_quotes(ex->quotes, (*input)[ex->i]);
		if ((*input)[ex->i] == 92)
		{
			check_esc_char(input, &ex->i, ex->quotes);
			if (!(*input)[ex->i])
				break ;
			if ((*input)[ex->i] != 92)
				ex->i++;
			continue ;
		}
		if ((*input)[ex->i] == '$')
			dollar_expansion(data, input, &ex->i, data->env_list);
		if (is_special_symbol((*input)[ex->i]))
			ex->i++;
		else if ((*input)[ex->i] == 39 && !ex->quotes)
			fordward_w_quote(*input, &ex->i);
		else if ((*input)[ex->i])
			ex->i++;
	}
	free(ex);
}

void	free_vars(t_expansion *vars)
{
	if (vars->str_back)
		free(vars->str_back);
	if (vars->str_front)
		free(vars->str_front);
	if (vars->tmp)
		free(vars->tmp);
	if (vars->var)
		free(vars->var);
}

t_token	*create_token(char *str, int index, int status)
{
	t_token	*token;

	if (!str)
		return (NULL);
	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
	{
		error_handle(ERR_UNKNOWN, "Minishell:",
			"lexing.c:206\nMalloc failed", KILL);
	}
	token->str = str;
	if (!status || (status && ft_strchr(token->str, '=')))
		token->type = get_type(token->str);
	else
		token->type = UNKNOW;
	token->index = index;
	return (token);
}

void	lexing_tokens(t_data *data, char **input)
{
	int		token_index;

	if (!(*input))
		return ;
	token_index = 0;
	check_for_expansion(data, input);
	tokenize(&data, input, token_index);
}

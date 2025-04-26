/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:31:14 by odruke-s          #+#    #+#             */
/*   Updated: 2025/04/22 15:25:18 by lomorale         ###   ########.fr       */
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
	int		i;
	int		quotes;

	i = 0;
	quotes = 0;
	while ((*input)[i])
	{
		quotes = is_in_quotes(quotes, (*input)[i]);
		if ((*input)[i] == 92)
		{
			check_esc_char(input, &i, quotes);
			if (!(*input)[i])
				break ;
			if ((*input)[i] != 92)
				i++;
			continue ;
		}
		if ((*input)[i] == '$')
			dollar_expansion(data, input, &i, data->env_list);
		if (is_special_symbol((*input)[i]))
			i++;
		else if ((*input)[i] == 39)
		{
			i++;
			while ((*input)[i] && (*input)[i] != 39)
				i++;
		}
		else if ((*input)[i])
			i++;
	}
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

t_token	*create_token(char *str, int index)
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
	token->type = get_type(token->str);
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

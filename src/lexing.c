/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:31:14 by odruke-s          #+#    #+#             */
/*   Updated: 2025/03/26 20:56:42 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



				/*MODIFY THIS ENTIRE FILE*/


#include "minishell.h"

static int	is_special_symbol(char c)
{
	char	*symbol_set;

	symbol_set = "|<>";
	while (*symbol_set)
	{
		if (*symbol_set == c)
			return (1);
		symbol_set++;
	}
	return (0);
}

static int	token_len(const char *input, int *i)
{
	int	len;

	len = 0;
	if (input[*i] == 39)
	{
		(*i)++;
		while (input[*i] && input[*i] != 39)
		{
			(*i)++;
			len++;
		}
	}
	else if (input[*i] == 34)
	{
		(*i)++;
		while (input[*i] && input[*i] != 34)
		{
			(*i)++;
			len++;
		}
	}
	else if (is_special_symbol(input[*i]))
	{
		(*i)++;
		len++;
	}
	else
	{
		while (input[*i] && !ft_isblank(input[*i]) && !is_special_symbol(input[*i]))
		{
			(*i)++;
			len++;
		}
	}
	return (len);
}

t_token *create_token(char *str, int index)
{
    t_token *token = malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->str = str;
    token->type = 0;
	token->index = index;
    return (token);
}

static void fill_token_list(t_data *data, char *token, int token_index)
{
	t_list	*new_node;
	t_token	*token_node;

	token_node = create_token(token, token_index);
	if (!token_node)
		error_handle(data, "token_node", "create_token failed", 1);
	new_node = ft_lstnew(token_node);
	if (!new_node)
		error_handle(data, "new_node", "ft_lstnew failed", 1);
	ft_lstadd_back(&data->token_list, new_node);
}

void	lexing_tokens(t_data *data, char *input)
{
	int		i;
	int		len;
	int		token_index;
	char	*tmp_token;

	i = 0;
	len = 0;
	token_index = -1;
	tmp_token = NULL;
	while (input[i])
	{
		if (!ft_isblank(input[i]))
		{
			token_index++;
			len = token_len(input, &i);
			tmp_token = ft_strndup(input + (i - len), len);
			if (!tmp_token)
				error_handle(data, "tmp_token", "ft_strndup failed", 1);
			fill_token_list(data, tmp_token, token_index);
		}
		if (input[i] == '\0')
			break ;
		else
			while (ft_isblank(input[i]))
				i++;
	}
}

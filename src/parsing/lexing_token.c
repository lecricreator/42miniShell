/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:02:39 by lomorale          #+#    #+#             */
/*   Updated: 2025/04/22 15:13:08 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_token_list(t_data *data, char *token, int token_index)
{
	t_list	*new_node;
	t_token	*token_node;

	token_node = create_token(token, token_index);
	new_node = ft_lstnew(token_node);
	if (!new_node)
		error_handle(ERR_UNKNOWN, "new_node",
			"lexing.c:224\nft_lstnew failed", KILL);
	ft_lstadd_back(&data->token_list, new_node);
}

void	tokenize(t_data **data, char **input, int token_index,
		int len)
{
	int		i;
	char	*token_str;
	char	*tmp;

	token_str = NULL;
	tmp = NULL;
	i = 0;
	while ((*input)[i])
	{
		while ((*input)[i] && !ft_isblank((*input)[i]))
		{
			token_index++;
			len = token_len(input, &i);
			if (!token_str)
			{
				token_str = ft_strndup((*input) + (i - len), len);
				if (!token_str)
					error_handle(ERR_UNKNOWN, "Minishell:",
						"lexing.c:251\nft_strndup failed", KILL);
			}
			else
			{
					tmp = token_str;
					token_str = ft_strnjoin(token_str, (*input) + (i - len), len);
					free(tmp);
			}
			if (is_special_symbol((*input)[i]) || is_special_symbol((*input)[i - 1]))
				break ;
		}	
		fill_token_list(*data, token_str, token_index);
		token_str = NULL;
		if ((*input)[i] == '\0')
			break ;
		if ((*input)[i] == 39 || (*input)[i] == 34)
			i++;
		else
			while (ft_isblank((*input)[i]))
				i++;
	}
}

static int	token_next_len(char **input, int *i, int *len)
{
	if (is_special_symbol(input[0][*i]))
	{
		if (is_double_symbol(*input, i))
		{
			(*i) += 2;
			(*len) = 2;
		}
		else
		{
			(*i)++;
			(*len)++;
		}
	}
	else
	{
		while (input[0][*i] && !ft_isblank(input[0][*i]) &&
				!is_special_symbol(input[0][*i]) && (*input)[*i] != 34 && (*input)[*i] != 39)
		{
			(*i)++;
			(*len)++;
		}
	}
	return (*len);
}

int	token_len(char **input, int *i)
{
	int	len;

	len = 0;
	if (input[0][*i] == 39)
	{
		(*i)++;
		while (input[0][*i] && input[0][*i] != 39)
		{
			(*i)++;
			len++;
		}
	}
	else if (input[0][*i] == 34)
	{
		(*i)++;
		while (input[0][*i] && input[0][*i] != 34)
		{
			(*i)++;
			len++;
		}
	}
	else
		len = token_next_len(input, i, &len);
	return (len);
}

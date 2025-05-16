/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:02:39 by lomorale          #+#    #+#             */
/*   Updated: 2025/04/24 21:12:12 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_token_list(t_data *data, char *token, int token_index, int status)
{
	t_list	*new_node;
	t_token	*token_node;

	token_node = create_token(token, token_index, status);
	if (!token_node)
		return ;
	new_node = ft_lstnew(token_node);
	if (!new_node)
		error_handle(ERR_UNKNOWN, "new_node",
			"lexing.c:224\nft_lstnew failed", KILL);
	ft_lstadd_back(&data->token_list, new_node);
}

static char	*tokenize_loop(char **input, int *i, int len, int *state)
{
	char	*token_str;
	char	*tmp;
	
	tmp = NULL;
	token_str = NULL;
	while ((*input)[*i] && !ft_isblank((*input)[*i]))
	{
		len = token_len(input, i, state);
		if (!token_str)
			token_str = ft_strndup((*input) + (*i - len), len);
		else
		{
			tmp = token_str;
			token_str = ft_strnjoin(token_str, (*input) + (*i - len), len);
			free(tmp);
		}
		if (*state && ((*input)[*i] == 39 || (*input)[*i] == 34))
			(*i)++;
		if (is_special_symbol((*input)[*i])
				|| is_special_symbol((*input)[*i - 1]))
			break ;
	}
	return (token_str);
}

void	tokenize(t_data **data, char **input, int token_index)
{
	int		i;
	int		len;
	int		state;
	char	*token_str;

	token_str = NULL;
	len = 0;
	i = 0;
	
	while ((*input)[i])
	{
		state = 0;
		token_str = tokenize_loop(input, &i, len, &state);
		if (token_str)
			fill_token_list(*data, token_str, token_index, state);
		token_index++;
		if ((*input)[i] == '\0')
			break ;
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
				!is_special_symbol(input[0][*i]) &&
				(*input)[*i] != 34 && (*input)[*i] != 39)
		{
			(*i)++;
			(*len)++;
		}
	}
	return (*len);
}

int	token_len(char **input, int *i, int *state)
{
	int	len;
	int	quote;

	len = 0;
	quote = 0;
	if (input[0][*i] == 39 || input[0][*i] == 34)
	{
		quote = input[0][*i];
		if (*state)
			*state = 0;
		else
			*state = 1;
		(*i)++;
		while (input[0][*i] && input[0][*i] != quote)
		{
			(*i)++;
			len++;
		}
	}
	else
		len = token_next_len(input, i, &len);
	return (len);
}

// int	token_len(char **input, int *i)
// {
// 	int	len;

// 	len = 0;
// 	if (input[0][*i] == 39)
// 	{
// 		(*i)++;
// 		while (input[0][*i] && input[0][*i] != 39)
// 		{
// 			(*i)++;
// 			len++;
// 		}
// 	}
// 	else if (input[0][*i] == 34)
// 	{
// 		(*i)++;
// 		while (input[0][*i] && input[0][*i] != 34)
// 		{
// 			(*i)++;
// 			len++;
// 		}
// 	}
// 	else
// 		len = token_next_len(input, i, &len);
// 	return (len);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:31:14 by odruke-s          #+#    #+#             */
/*   Updated: 2025/04/04 01:40:19 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	is_double_arrow(const char *input, int *i)
{
	if (input[*i] == '>' && input[*i + 1] == '>')
		return (1);
	else if (input[*i] == '<' && input[*i + 1] == '<')
		return (1);
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
		if (is_double_arrow(input, i))
		{
			(*i) += 2;
			len = 2;
		}
		else
		{
			(*i)++;
			len++;
		}
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
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
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

static int	get_type(char *token)
{
	if (!ft_strncmp(token, "echo", ft_strlen(token)))
		return (BI_ECHO);
	if (!ft_strncmp(token, "cd", ft_strlen(token)))
		return (BI_CD);
	if (!ft_strncmp(token, "pwd", ft_strlen(token)))
		return (BI_PWD);
	if (!ft_strncmp(token, "export", ft_strlen(token)))
		return (BI_EXPORT);
	if (!ft_strncmp(token, "unset", ft_strlen(token)))
		return (BI_UNSET);
	if (!ft_strncmp(token, "env", ft_strlen(token)))
		return (BI_ENV);
	if (!ft_strncmp(token, "exit", ft_strlen(token)))
		return (BI_EXIT);
	if (!ft_strncmp(token, "|", ft_strlen(token)))
		return (OP_PIPE);
	if (!ft_strncmp(token, ">", ft_strlen(token)))
		return (OP_REDIR_OUT);
	if (!ft_strncmp(token, "<", ft_strlen(token)))
		return (OP_REDIR_IN);
	if (!ft_strncmp(token, ">>", ft_strlen(token)))
		return (OP_APPEND);
	if (!ft_strncmp(token, "<<", ft_strlen(token)))
		return (OP_HEREDOC);
	return (UNKNOW);
}

static void	fill_types(t_data *data)
{
	t_token	*tmp_token;
	t_list	*tmp_head;

	tmp_head = data->token_list;
	while (tmp_head)
	{
		tmp_token = (t_token *)tmp_head->content;
		tmp_token->type = get_type(tmp_token->str);
		tmp_head = tmp_head->next;
	}
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
		if (input[i] == 39 || input[i] == 34)
			i++;
		else
			while (ft_isblank(input[i]))
				i++;
	}
	fill_types(data);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:31:14 by odruke-s          #+#    #+#             */
/*   Updated: 2025/04/11 17:29:09 by lomorale         ###   ########.fr       */
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

void	init_exp(t_expansion *exp, int start)
{
	exp->i = start + 1;
	exp->new_input = NULL;
	exp->str_back = NULL;
	exp->str_front = NULL;
	exp->var = NULL;
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

char	*dollar_expansion(t_data *data, char *input, int *start, t_list *env_list)
{
	t_expansion	vars;

	init_exp(&vars, *start);
	if (input[vars.i] == '?')
	{
		vars.var = ft_itoa(data->status);
		vars.i++;
	}
	else
	{
		while (input[vars.i] && !ft_isblank(input[vars.i]))
			vars.i++;
		vars.var = ft_strndup(input + (*start + 1),  vars.i - *start - 1);
		vars.tmp = vars.var;
		vars.var = ft_strdup(give_var_env_list(vars.var, env_list));
		free(vars.tmp);
	}
	if (!vars.var)
		vars.var = ft_strdup("");
	vars.str_front = ft_strndup(input, *start);
	vars.str_back = ft_strdup(input + vars.i);
	vars.new_input = ft_strjoin(vars.str_front, vars.var);
	vars.tmp = vars.new_input;
	vars.new_input = ft_strjoin(vars.new_input, vars.str_back);
	*start += ft_strlen(vars.var);
	free_vars(&vars);
	return (vars.new_input);
}
void	check_for_expansion(t_data *data, char **input)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while ((*input)[i])
	{
		if ((*input)[i] == '$')
		{	
			tmp = *input;
			*input = dollar_expansion(data, *input, &i, data->env_list);
			free(tmp);
		}
		if (is_special_symbol((*input)[i]))
			i++;
		while ((*input)[i] == 34)
			i++;
		while ((*input)[i] == 39)
			i++;
		if ((*input)[i])
			i++;
	}
}

static int	token_len(char **input, int *i)
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
	else if (is_special_symbol(input[0][*i]))
	{
		if (is_double_arrow(*input, i))
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
		while (input[0][*i] && !ft_isblank(input[0][*i]) && !is_special_symbol(input[0][*i]))
		{
			(*i)++;
			len++;
		}
	}
	return (len);
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

t_token *create_token(char *str, int index)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = str;
	token->type = get_type(token->str);
	token->index = index;
	return (token);
}

static void fill_token_list(t_data *data, char *token, int token_index)
{
	t_list	*new_node;
	t_token	*token_node;

	token_node = create_token(token, token_index);
	if (!token_node)
		error_handle(data, "token_node", "lexing.c:190\ncreate_token failed", 1);
	new_node = ft_lstnew(token_node);
	if (!new_node)
		error_handle(data, "new_node", "lexing.c:193\nft_lstnew failed", 1);
	ft_lstadd_back(&data->token_list, new_node);
}

void	lexing_tokens(t_data *data, char **input)
{
	int		i;
	int		len;
	int		token_index;
	char	*token_str;

	if (!(*input))
		return ;
	i = 0;
	len = 0;
	token_index = -1;
	token_str = NULL;
	check_for_expansion(data, input);
	while ((*input)[i])
	{
		if (!ft_isblank((*input)[i]))
		{
			token_index++;
			len = token_len(input, &i);
			token_str = ft_strndup((*input) + (i - len), len);
			if (!token_str)
				error_handle(data, "token_str", "lexing.c:216\nft_strndup failed", 1);
			fill_token_list(data, token_str, token_index);
		}
		if ((*input)[i] == '\0')
			break ;
		if ((*input)[i] == 39 || (*input)[i] == 34)
			i++;
		else
			while (ft_isblank((*input)[i]))
				i++;
	}
}

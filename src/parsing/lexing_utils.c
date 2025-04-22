/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:19:14 by lomorale          #+#    #+#             */
/*   Updated: 2025/04/22 14:04:07 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_special_symbol(char c)
{
	char	*symbol_set;

	symbol_set = "|<>&;(){}";
	while (*symbol_set)
	{
		if (*symbol_set == c)
			return (1);
		symbol_set++;
	}
	return (0);
}

int	is_double_symbol(const char *input, int *i)
{
	if (input[*i] == input[*i + 1])
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

static void	transform_dollar(t_expansion *vars, char **input, int **start)
{
	if (!vars->var)
		vars->var = ft_strdup("");
	vars->str_front = ft_strndup(*input, **start);
	vars->str_back = ft_strdup(*input + vars->i);
	vars->new_input = ft_strjoin(vars->str_front, vars->var);
	vars->tmp = vars->new_input;
	vars->new_input = ft_strjoin(vars->new_input, vars->str_back);
	*start += ft_strlen(vars->var);
	free_vars(vars);
}

char	*dollar_expansion(t_data *data, char *input, int *start,
		t_list *env_list)
{
	t_expansion	vars;

	init_exp(&vars, *start);
	if (!input[vars.i] || ft_isblank(input[vars.i]))
		vars.var = ft_strdup("$");
	else if (input[vars.i] == '?')
	{
		vars.var = ft_itoa(data->status);
		vars.i++;
	}
	else
	{
		while (input[vars.i] && !ft_isblank(input[vars.i]) && input[vars.i]
			!= 34)
			vars.i++;
		vars.var = ft_strndup(input + (*start + 1), vars.i - *start - 1);
		vars.tmp = vars.var;
		vars.var = ft_strdup(give_var_env_list(vars.var, env_list));
		free(vars.tmp);
	}
	transform_dollar(&vars, &input, &start);
	return (vars.new_input);
}

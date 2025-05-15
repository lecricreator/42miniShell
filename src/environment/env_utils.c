/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 19:39:01 by odruke-s          #+#    #+#             */
/*   Updated: 2025/04/20 23:36:37 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	var_syntax(char *var)
{
	int	i;

	i = 0;
	if (!ft_isalpha(var[i]) && var[i] != '_')
		return (0);
	i++;
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]))
			if (var[i] != '+' || var[i + 1] != '=')
				return (0);
		i++;
	}
	return (1);
}

int	var_len(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	return (i);
}

void	update_var_value(t_env **var, char *new_value)
{
	char	*tmp;
	char	*var_name;

	tmp = NULL;
	var_name = NULL;
	tmp = (*var)->var;
	var_name = ft_strndup((*var)->var, var_len((*var)->var) + 1);
	(*var)->var = ft_strjoin(var_name, new_value);
	if (tmp)
		free(tmp);
	if (var_name)
		free(var_name);
}

void	concat_var_value(t_env **var, char *new_value)
{
	char	*tmp;

	tmp = NULL;
	tmp = (*var)->var;
	(*var)->var = ft_strjoin((*var)->var, new_value);
	if (tmp)
		free(tmp);
}

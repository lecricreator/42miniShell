/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_built.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 22:09:48 by lomorale          #+#    #+#             */
/*   Updated: 2025/04/21 21:09:14 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*give_var_env_list(char *var_name, t_list *env_list)
{
	char	*env_var;
	while (env_list)
	{
		env_var = ((t_env *)(env_list)->content)->var;
		if (!ft_strncmp_env_var(var_name, env_var, var_len(var_name)))
			return (&env_var[var_len(env_var) + 1]);
		env_list = env_list->next;
	}
	return (NULL);
}

void	write_env_list(char *new_value, char *var_name, t_list **env_list)
{
	char	*env_var;
	t_list	*head_env;

	head_env = *env_list;
	while (*env_list)
	{
		env_var = ((t_env *)(*env_list)->content)->var;
		if (!ft_strncmp_exact(env_var, var_name, var_len(var_name)))
		break ;
		*env_list = (*env_list)->next;
	}
	if (*env_list)
	{
		((t_env *)(*env_list)->content)->var = ft_strjoin(var_name,
				new_value);
	}
	(*env_list) = head_env;
}

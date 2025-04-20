/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_built.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 22:09:48 by lomorale          #+#    #+#             */
/*   Updated: 2025/04/20 23:07:52 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*give_var_env_list(char *var_name, t_list *env_list)
{
	char	*tmp_content;
	int		var_name_len;

	var_name_len = (int)ft_strlen(var_name);
	while (env_list)
	{
		tmp_content = ((t_env *)(env_list)->content)->var;
		if (ft_strncmp_env_var(var_name, tmp_content, var_name_len) == 0)
		{
			return (&tmp_content[var_name_len]);
		}
		env_list = env_list->next;
	}
	return (NULL);
}

void	write_env_list(char *value_modify, char *env_value, t_list **env_list)
{
	char	*tmp_content;
	t_list	*head_env;
	int		size_value;

	head_env = *env_list;
	size_value = (int)ft_strlen(env_value);
	while (*env_list)
	{
		tmp_content = ((t_env *)(*env_list)->content)->var;
		if (ft_strncmp_env_var(env_value, tmp_content, size_value) == 0)
		{
			break ;
		}
		*env_list = (*env_list)->next;
	}
	if (*env_list)
	{
		((t_env *)(*env_list)->content)->var = ft_strjoin(env_value,
				value_modify);
	}
	(*env_list) = head_env;
}

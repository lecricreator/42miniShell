/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in_unset.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:35:45 by lomorale          #+#    #+#             */
/*   Updated: 2025/04/26 01:26:38 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	verif_delete(char **cmd_args, t_list **env_list,
	t_env *tmp_env, int *i)
{
	if (ft_strchr(cmd_args[*i], '=') || !ft_strncmp(cmd_args[*i], "_=", 2))
	{
		i++;
		return (1);
	}
	if (!ft_strncmp_env_var(cmd_args[*i], tmp_env->var, var_len(cmd_args[*i])))
	{
		ft_lstdel_node(env_list, free_env);
		i++;
		return (1);
	}
	return (0);
}

int	exec_unset(char **cmd_args, t_list **env_list)
{
	t_list	*tmp_head;
	t_env	*tmp_env;
	int		i;

	i = 1;
	while (cmd_args[i])
	{
		tmp_head = *env_list;
		tmp_env = (t_env *)tmp_head->content;
		if (verif_delete(cmd_args, env_list, tmp_env, &i))
			continue ;
		while (tmp_head && tmp_head->next)
		{
			tmp_env = (t_env *)tmp_head->next->content;
			if (!ft_strncmp_env_var(cmd_args[i], tmp_env->var,
					var_len(cmd_args[i])))
			{
				ft_lstdel_nxtnode(&tmp_head, free_env);
				continue ;
			}
			tmp_head = tmp_head->next;
		}
		i++;
	}
	return (0);
}

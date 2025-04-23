/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in_unset.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:35:45 by lomorale          #+#    #+#             */
/*   Updated: 2025/04/23 18:20:22 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_unset(char **cmd_args, t_list **env_list)
{
	t_list	*tmp_head;
	t_env	*tmp_env;
	int		i;

	i = 1;
	while (cmd_args[i])
	{
		if (ft_strchr(cmd_args[i], '=') || !ft_strncmp(cmd_args[i], "_=", 2))
		{
			i++;
			continue ;
		}
		tmp_head = *env_list;
		tmp_env = (t_env *)tmp_head->content;
		if (!ft_strncmp_env_var(cmd_args[i], tmp_env->var, var_len(cmd_args[i])))
		{
			ft_lstdel_node(env_list, free_env);
			i++;
			continue ;
		}
		while (tmp_head && tmp_head->next)
		{
			tmp_env = (t_env *)tmp_head->next->content;
			if (!ft_strncmp_env_var(cmd_args[i], tmp_env->var, var_len(cmd_args[i])))
			{
				ft_lstdel_nxtnode(&tmp_head, free_env);
				break ;
			}
			tmp_head = tmp_head->next;
		}
		i++;
	}
	return (0);
}

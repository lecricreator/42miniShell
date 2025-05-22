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

static void	check_to_delete(char *var, t_list **env_list)
{
	t_list	*tmp_head;
	t_env	*tmp_env;

	tmp_env = (t_env *)(*env_list)->content;
	if (!ft_strncmp_env_var(var, tmp_env->var, var_len(var)))
	{
		ft_lstdel_node(env_list, free_env);
		return ;
	}
	tmp_head = *env_list;
	while (tmp_head && tmp_head->next)
	{
		tmp_env = (t_env *)tmp_head->next->content;
		if (!ft_strncmp_env_var(var, tmp_env->var, var_len(var)))
		{
			ft_lstdel_nxtnode(&tmp_head, free_env);
			break ;
		}
		tmp_head = tmp_head->next;
	}
}

int	exec_unset(char **cmd_args, t_list **env_list)
{
	int		i;

	i = 1;
	while (cmd_args[i])
	{
		if (!ft_strcmp(cmd_args[i], "_"))
		{
			i++;
			continue ;
		}
		check_to_delete(cmd_args[i], env_list);
		i++;
	}
	return (0);
}

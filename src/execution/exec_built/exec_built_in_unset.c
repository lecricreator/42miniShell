/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in_unset.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:35:45 by lomorale          #+#    #+#             */
/*   Updated: 2025/04/23 17:00:06 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_list_in_liked_list(t_list **env_list,
		t_list	**tmp_linked_list_at_delete, t_list	*tmp_head, int first)
{
	if (!first)
	{
		free(((t_env *)(*env_list)->next->content)->var);
		*tmp_linked_list_at_delete = (*env_list);
		(*env_list)->next = (*env_list)->next->next;
		free(*tmp_linked_list_at_delete);
		(*env_list) = tmp_head;
	}
	else
	{
		free(((t_env *)(*env_list)->content)->var);
		*tmp_linked_list_at_delete = (*env_list);
		(*env_list) = (*env_list)->next;
		ft_printf_fd(2, "%s\n", ((t_env *)(*env_list)->content)->var);
		free(*tmp_linked_list_at_delete);
	}
}

int	exec_unset(char **cmd_args, t_list **env_list)
{
	t_list	*tmp_head;
	t_list	*tmp_linked_list_at_delete;

	tmp_head = *env_list;
	if (ft_strchr(cmd_args[1], '=') != 0)
		return (0);
	if (give_var_env_list(cmd_args[1], *env_list))
	{
		if (ft_strncmp(cmd_args[1], ((t_env *)(*env_list)->content)->var,
				ft_strlen(cmd_args[1])) == 0)
				{
					delete_list_in_liked_list(env_list, &tmp_linked_list_at_delete,
						tmp_head, 1);
					ft_printf_fd(2, "%s\n", *((t_env *)(*env_list)->content)->var);
					return(0);
				}
		while ((*env_list)->next)
		{
			if (ft_strncmp(cmd_args[1], ((t_env *)(*env_list)->next->content)->var,
				ft_strlen(cmd_args[1])) == 0)
				delete_list_in_liked_list(env_list, &tmp_linked_list_at_delete,
						tmp_head, 0);
			(*env_list) = (*env_list)->next;
		}
	}
	return (0);
}

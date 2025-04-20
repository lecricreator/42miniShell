/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in_unset.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:35:45 by lomorale          #+#    #+#             */
/*   Updated: 2025/04/20 15:47:52 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_unset(char **cmd_args, t_list **env_list)
{
	t_list	*tmp_head;
	t_list	*tmp_linked_list_at_delete;

	tmp_head = *env_list;
	if (ft_strchr(cmd_args[1], '=') != 0)
		return ;
	if (give_var_env_list(cmd_args[1], *env_list))
	{
		while ((*env_list)->next)
		{
			if (strncmp(cmd_args[1], ((t_env *)(*env_list)->next->content)->var,
				ft_strlen(cmd_args[1])) == 0)
			{
				free(((t_env *)(*env_list)->next->content)->var);
				tmp_linked_list_at_delete = (*env_list)->next;
				(*env_list)->next = (*env_list)->next->next;
				free(tmp_linked_list_at_delete);
				(*env_list) = tmp_head;
				break ;
			}
			(*env_list) = (*env_list)->next;
		}
	}
}

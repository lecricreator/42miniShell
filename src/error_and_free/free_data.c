/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 02:08:12 by odruke-s          #+#    #+#             */
/*   Updated: 2025/04/04 02:08:27 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(t_list **list, void (*del)(void *))
{
	t_list	*tmp;

	if (!list || !*list)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		if ((*list)->content && del)
			del((*list)->content);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
}

void	free_data(t_data *data)
{
	if (data->input)
		free(data->input);
	if (data->env_list)
		free_list(&data->env_list, free);
	if (data->token_list)
		free_list(&data->token_list, free_token);
	if (data->cmd_list)
		free_list(&data->cmd_list, free_cmd);
	if (data)
		free(data);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_nxtnode.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 01:18:13 by odruke-s          #+#    #+#             */
/*   Updated: 2025/04/08 01:20:22 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel_nxtnode(t_list **list, void (*del)(void *))
{
	t_list	*tmp;

	if (!list || !*list || !(*list)->next)
		return ;
	tmp = (*list)->next;
	if ((*list)->next->next)
		(*list)->next = (*list)->next->next;
	else
	{
		(*list)->next = NULL;
	}
	if (tmp->content && del)
		del(tmp->content);
	free(tmp);
}

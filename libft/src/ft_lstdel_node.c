/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 01:17:18 by odruke-s          #+#    #+#             */
/*   Updated: 2025/04/08 01:17:55 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel_node(t_list **list, void (*del)(void *))
{
	t_list	*tmp;

	if (!list || !*list)
		return ;
	tmp = *list;
	*list = (*list)->next;
	if (tmp->content && del)
		del(tmp->content);
	free(tmp);
}

#include "libft.h"

void	ft_lstdel_node(t_list **list, void (*del)(void *))
{
	t_list	*tmp;

	if (!list || !*list)
		return ;
	tmp = (*list)->next;
	if ((*list)->content && del)
		del((*list)->content);
	free(*list);
	*list = tmp;
}
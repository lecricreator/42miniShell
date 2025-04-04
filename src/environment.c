/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 01:50:06 by odruke-s          #+#    #+#             */
/*   Updated: 2025/04/04 01:50:11 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_list *env_list)
{
	while (env_list)
	{
		printf("%s\n", (char *)env_list->content);
		env_list = env_list->next;
	}
}

void	get_env(t_list **env_list, char **env)
{
	char	*tmp_content;
	int		i;

	i = 0;
	tmp_content = NULL;
	while (env[i])
	{
		tmp_content = ft_strdup(env[i]);
		if (!tmp_content)
			return ;
		ft_lstadd_back(env_list, ft_lstnew(tmp_content));
		i++;
	}
}

static int	env_size(t_list *env_list)
{
	t_list	*tmp_head;
	inti	i;

	i = 0;
	tmp_head = env_list;
	while (tmp_head)
	{
		i++;
		tmp_head = tmp_head->next;
	}
	return (i);
}

char	**get_env_tab(t_list *env_list)
{
	t_list	*tmp_head;
	char	**env_tab;
	int		i;

	i = 0;
	tmp_head = env_list;
	env_tab = (char **)malloc(sizeof(char *) * (env_size(env_list) + 1));
	if (!env_tab)
		error_handle(NULL, "env_tab function", "environment.c:53 malloc failed", 1); // change this line
	while (tmp_head)
	{
		env_tab[i++] = ft_strdup((char *)tmp_head->content);
		tmp_head = tmp_head->next;
	}
	env_tab[i] = NULL;
	return (env_tab);
}

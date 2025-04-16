/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 01:50:06 by odruke-s          #+#    #+#             */
/*   Updated: 2025/04/04 15:58:04 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	get_env(t_list **env_list, char **env)
{
	t_env	*node;
	int		i;

	i = 0;
	while (env[i])
	{
		node = (t_env *)malloc(sizeof(t_env));
		node->exported = 1;
		node->var = ft_strdup(env[i]);
		if (!node->var)
			return ;
		ft_lstadd_back(env_list, ft_lstnew(node));
		i++;
	}
}

static int	env_size(t_list *env_list)
{
	t_list	*tmp_head;
	t_env	*tmp_var;
	int		i;

	i = 0;
	tmp_head = env_list;
	tmp_var = (t_env *)env_list->content;
	while (tmp_head)
	{
		if (tmp_var->exported)
			i++;
		tmp_head = tmp_head->next;
		if (tmp_head)
			tmp_var = (t_env *)env_list->content;
	}
	return (i);
}

char	**get_env_tab(t_list *env_list)
{
	t_list	*tmp_head;
	t_env	*tmp_var;
	char	**env_tab;
	int		i;

	i = 0;
	tmp_head = env_list;
	tmp_var = (t_env *)tmp_head->content;
	env_tab = (char **)malloc(sizeof(char *) * (env_size(env_list) + 1));
	if (!env_tab)
		error_handle(NULL, "env_tab function", "environment.c:53 malloc failed", 1); // change this line
	while (tmp_head)
	{
		if (tmp_var->exported)
			env_tab[i++] = ft_strdup(tmp_var->var);
		tmp_head = tmp_head->next;
		if (tmp_head)
			tmp_var = (t_env *)tmp_head->content;
	}
	env_tab[i] = NULL;
	return (env_tab);
}

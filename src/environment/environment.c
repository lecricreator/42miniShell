/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 01:50:06 by odruke-s          #+#    #+#             */
/*   Updated: 2025/04/21 19:56:06 by lomorale         ###   ########.fr       */
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

char	**add_env(char **env_tab, t_list *env_list, char **tmp_var)
{
	t_list	*tmp_head;
	t_env	*tmp_env_var;
	int		i;
	int		b;

	i = 0;
	b = 0;
	tmp_head = env_list;
	while (tmp_head)
	{
		tmp_env_var = (t_env *)tmp_head->content;
		if (tmp_env_var->exported)
			env_tab[i++] = ft_strdup(tmp_env_var->var);
		tmp_head = tmp_head->next;
		if (tmp_head)
			tmp_env_var = (t_env *)tmp_head->content;
	}
	while (tmp_var && tmp_var[b])
	{
		env_tab[i++] = ft_strdup(tmp_var[b]);
		i++;
		b++;
	}
	env_tab[i] = NULL;
	return (env_tab);
}

char	**get_env_tab(t_list *env_list, char **tmp_var)
{
	char	**env_tab;

	if (!tmp_var)
		env_tab = (char **)malloc(sizeof(char *) * (env_size(env_list) + 1));
	else
		env_tab = (char **)malloc(sizeof(char *) * ((env_size(env_list)
						+ count_table(tmp_var) + 1)));
	if (!env_tab)
		error_handle(ERR_UNKNOWN, "Minishell:",
			"environment.c:92\nmalloc failed", KILL);
	env_tab = add_env(env_tab, env_list, tmp_var);
	return (env_tab);
}

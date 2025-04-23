/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 01:50:06 by odruke-s          #+#    #+#             */
/*   Updated: 2025/04/23 17:18:26 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*appears 1 / not apears 0*/
void	env_is_empty(t_env *node, t_list **env_list, char *str, int exported)
{
	node = (t_env *)malloc(sizeof(t_env));
	node->exported = exported;
	node->var = ft_strdup(str);
	if (!node->var)
		error_handle(ERR_UNKNOWN,
				"Minishell$", "ERROR MALLOC  environment.c", 0);
	ft_lstadd_back(env_list, ft_lstnew(node));
}

void	get_env(t_list **env_list, char **env)
{
	t_env	*node;
	int		i;
	char	buffer[1024];
	char	*join;

	i = 0;
	node = NULL;
	if (!*env)
	{
		env_is_empty(node, env_list, "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin", 1);
		join = ft_strjoin("PWD=", getcwd(buffer, sizeof(buffer)));
		env_is_empty(node, env_list, join, 1);
		free(join);
		env_is_empty(node, env_list, "OLDPWD=", 0);
		env_is_empty(node, env_list, "SHLVL=1", 1);
		(*env_list)->next = NULL;
	}
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

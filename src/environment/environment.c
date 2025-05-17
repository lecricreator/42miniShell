/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 01:50:06 by odruke-s          #+#    #+#             */
/*   Updated: 2025/04/24 15:40:16 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *update_shlvl(char *var)
{
	int		lvl;
	int		blen;
	int		flen;
	int		nlen;
	char	*res;
	char	*tmp;
	char	*number;

	lvl = 1;
	blen = 0;
	flen = 0;
	nlen = 0;
	while (var[flen] && !ft_isdigit(var[flen]))
		flen++;
	while (var[flen + nlen] && ft_isdigit(var[flen + nlen]))
		nlen++;
	while (var[flen + nlen + blen])
		blen++;
	number = ft_strndup(var + flen, nlen);
	lvl = ft_atoi(number);
	free(number);
	lvl += 1;
	number = ft_itoa(lvl);
	tmp = ft_strndup(var, flen);
	res = ft_strjoin(tmp, number);
	free(number);
	free(tmp);
	tmp = res;
	res = ft_strjoin(res, var + (flen + nlen));
	free(tmp);
	return (res);
}

char	*get_shell_addr(void)
{
	char	*res;
	char	*tmp;
	char	buffer[1024];

	getcwd(buffer, sizeof(buffer));
	tmp = ft_strjoin("SHELL=", buffer);
	res = ft_strjoin(tmp, "/minishell");
	free(tmp);
	return (res);
}

void	get_env(t_list **env_list, char **env)
{
	t_env	*node;
	int		i;

	i = 0;
	node = NULL;
	if (!*env)
	{
		empty_env(env_list, node);
		return;
	}
	while (env[i])
	{
		node = (t_env *)malloc(sizeof(t_env));
		node->exported = 1;
		if (!ft_strncmp(env[i], "SHLVL=", 6))
			node->var = update_shlvl(env[i]);
		else if(!ft_strncmp(env[i], "SHELL=", 6))
			node->var = get_shell_addr();
		else
			node->var = ft_strdup(env[i]);
		if (!node->var)
			return ;
		ft_lstadd_back(env_list, ft_lstnew(node));
		i++;
	}
	if (!give_var_env_list("OLDPWD", *env_list))
	{
		node = (t_env *)malloc(sizeof(t_env));
		node->exported = 1;
		node->var = ft_strdup("OLDPWD");
		if (!node->var)
			return ;
		ft_lstadd_back(env_list, ft_lstnew(node));
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:23:45 by odruke-s          #+#    #+#             */
/*   Updated: 2025/05/19 18:43:05 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_vars(t_shlvl_vars *var)
{
	var->lvl = 1;
	var->flen = 0;
	var->nlen = 0;
	var->number = NULL;
	var->res = NULL;
	var->tmp = NULL;
}

char	*update_shlvl(char *env_var)
{
	t_shlvl_vars	var;

	init_vars(&var);
	while (env_var[var.flen] && !ft_isdigit(env_var[var.flen]))
		var.flen++;
	while (env_var[var.flen + var.nlen]
		&& ft_isdigit(env_var[var.flen + var.nlen]))
		var.nlen++;
	var.number = ft_strndup(env_var + var.flen, var.nlen);
	var.lvl = ft_atoi(var.number);
	free(var.number);
	var.lvl += 1;
	var.number = ft_itoa(var.lvl);
	var.tmp = ft_strndup(env_var, var.flen);
	var.res = ft_strjoin(var.tmp, var.number);
	free(var.number);
	free(var.tmp);
	var.tmp = var.res;
	var.res = ft_strjoin(var.res, env_var + (var.flen + var.nlen));
	free(var.tmp);
	return (var.res);
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

void	set_oldpwd(t_list **env_list)
{
	t_env	*node;

	node = NULL;
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

void	get_env(t_list **env_list, char **env)
{
	t_env	*node;
	int		i;

	i = 0;
	node = NULL;
	if (!*env)
		return (empty_env(env_list, node));
	while (env[i])
	{
		node = (t_env *)malloc(sizeof(t_env));
		node->exported = 1;
		if (!ft_strncmp(env[i], "SHLVL=", 6))
			node->var = update_shlvl(env[i]);
		else if (!ft_strncmp(env[i], "SHELL=", 6))
			node->var = get_shell_addr();
		else
			node->var = ft_strdup(env[i]);
		if (!node->var)
			return ;
		ft_lstadd_back(env_list, ft_lstnew(node));
		i++;
	}
	set_oldpwd(env_list);
}

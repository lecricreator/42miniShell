/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:13:06 by lomorale          #+#    #+#             */
/*   Updated: 2025/04/24 21:43:51 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_env_empty(t_env *node, t_list **env_list, char *str,
		int exported)
{
	node = (t_env *)malloc(sizeof(t_env));
	node->exported = exported;
	node->var = ft_strdup(str);
	if (!node->var)
		error_handle(ERR_UNKNOWN,
			"Minishell$", "ERROR MALLOC  environment.c", 0);
	ft_lstadd_back(env_list, ft_lstnew(node));
}

void	empty_env(t_list **env_list, t_env	*node)
{
	char	buffer[1024];
	char	*join;

	add_env_empty(node, env_list, "OLDPWD", 1);
	add_env_empty(node, env_list,
		"PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin", 0);
	join = ft_strjoin("PWD=", getcwd(buffer, sizeof(buffer)));
	add_env_empty(node, env_list, join, 1);
	free(join);
	add_env_empty(node, env_list, "SHLVL=1", 1);
	add_env_empty(node, env_list, "_=./mini_shell", 0);
}

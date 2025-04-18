/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_print_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 19:39:15 by odruke-s          #+#    #+#             */
/*   Updated: 2025/04/18 11:58:29 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_list *env_list)
{
	t_env	*tmp_var;

	tmp_var = (t_env *)env_list->content;
	while (env_list)
	{
		if (tmp_var->exported)
			printf("%s\n", tmp_var->var);
		env_list = env_list->next;
		if (env_list)
		tmp_var = (t_env *)env_list->content;
	}
}

static void	ft_swap(char **var_a, char **var_b)
{
	char	*tmp;

	tmp = *var_a;
	*var_a = *var_b;
	*var_b = tmp;
}

static void	sort_env_tab(char **env_tab)
{
	int		i;
	int		b;
	char	*var_a;
	char	*var_b;

	i = 0;
	var_a = NULL;
	var_b = NULL;
	while (env_tab[i])
	{
		b = 0;
		while (env_tab[b] && env_tab[b + 1])
		{
			var_a = strdup_limiter(env_tab[b], '=');
			var_b = strdup_limiter(env_tab[b + 1], '=');
			if (ft_strcmp(var_a, var_b) > 0)
				ft_swap(&env_tab[b], &env_tab[b + 1]);
			free(var_a);
			free(var_b);
			b++;
		}
		i++;
	}
}

void	print_export(t_list *env_list)
{
	int		i;
	char	**env_tab;
	char	*var_name;
	char	*var_value;

	i = 0;
	env_tab = get_env_tab(env_list, NULL);
	sort_env_tab(env_tab);
	while (env_tab[i])
	{
		var_name = strdup_limiter(env_tab[i], '=');
		if (ft_strchr(env_tab[i], '='))
			var_value = ft_strdup(env_tab[i] + (var_len(env_tab[i]) + 1));
		else
			var_value = ft_strdup("");
		ft_printf_fd(1, "declare -x %s=\"%s\"\n", var_name, var_value);
		free(var_name);
		free(var_value);
		i++;
	}
	free(env_tab);
}

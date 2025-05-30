/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_print_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 19:39:15 by odruke-s          #+#    #+#             */
/*   Updated: 2025/04/25 23:36:04 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_env(t_list *env_list, t_cmd *cmd)
{
	t_env	*tmp_var;

	if (cmd->cmd_args[0] && cmd->cmd_args[1])
		return (error_handle(ERR_NO_FILE_X, cmd->cmd_args[1], NULL, CONTINUE));
	tmp_var = (t_env *)env_list->content;
	while (env_list)
	{
		if (tmp_var->exported && ft_strchr(tmp_var->var, '='))
			printf("%s\n", tmp_var->var);
		env_list = env_list->next;
		if (env_list)
			tmp_var = (t_env *)env_list->content;
	}
	return (0);
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

void	write_line_env(int *i, char *var_name, char **env_tab, char *var_value)
{
	if (!ft_strncmp(var_name, "_", ft_strlen(var_name)))
	{
		i++;
		return ;
	}
	if (ft_strchr(env_tab[*i], '='))
		var_value = ft_strdup(env_tab[*i] + (var_len(env_tab[*i]) + 1));
	else
		var_value = ft_strdup("");
	if (ft_strchr(env_tab[*i], '='))
		ft_printf_fd(1, "declare -x %s=\"%s\"\n", var_name, var_value);
	else
		ft_printf_fd(1, "declare -x %s\n", env_tab[*i]);
	free(var_value);
	return ;
}

void	print_export(t_list *env_list)
{
	int		i;
	char	**env_tab;
	char	*var_name;
	char	*var_value;

	i = 0;
	var_value = NULL;
	env_tab = get_env_tab(env_list, NULL);
	sort_env_tab(env_tab);
	while (env_tab[i])
	{
		var_name = strdup_limiter(env_tab[i], '=');
		write_line_env(&i, var_name, env_tab, var_value);
		free(var_name);
		i++;
	}
	free_table(env_tab);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in_export.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:35:45 by lomorale          #+#    #+#             */
/*   Updated: 2025/05/15 20:24:38 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_var_in_env(char **cmd_args, int i,
		t_list	**tmp_head, t_list **env_list)
{
	char	*tmp;

	tmp = NULL;
	if (*tmp_head)
	{
		if (ft_strchr(cmd_args[i], '='))
		{
			if ((ft_strchr(cmd_args[i], '=') - 1)[0] == '+')
				concat_var_value((t_env **)&(*tmp_head)->content,
					cmd_args[i] + ((var_len(cmd_args[i]) + 1)));
			else
			{
				tmp = ((t_env *)(*tmp_head)->content)->var;
				((t_env *)(*tmp_head)->content)->var = ft_strdup(cmd_args[i]);
				((t_env *)(*tmp_head)->content)->exported = 1;
				free(tmp);
			}
		}
		else
			((t_env *)(*tmp_head)->content)->exported = 1;
	}
	else
		add_var(env_list, cmd_args[i], 1);
}

void	verified_var_exist_in_env(char **cmd_args, t_list **env_list, int i)
{
	t_list	*tmp_head;
	char	*env_var;
	char	*var_name;

	var_name = NULL;
	tmp_head = *env_list;
	while (tmp_head)
	{
		env_var = ((t_env *)(tmp_head)->content)->var;
		var_name = strdup_limiter(cmd_args[i], '=');
		if (!ft_strncmp_env_var(var_name, env_var, var_len(var_name)))
		{
			free(var_name);
			break ;
		}
		else if (var_name[var_len(var_name) - 1] == '+'
			&& !ft_strncmp_env_var(var_name, env_var, var_len(var_name) - 1))
		{
			free(var_name);
			break ;
		}
		tmp_head = (tmp_head)->next;
		free(var_name);
	}
	add_var_in_env(cmd_args, i, &tmp_head, env_list);
}

int	exec_export(char **cmd_args, t_list **env_list)
{
	int		i;

	if (!cmd_args[1])
		return (print_export(*env_list), 0);
	i = 1;
	while (cmd_args[i])
	{
		if (!var_syntax(cmd_args[i]))
			return (error_handle(ERR_INVAL_IDE, cmd_args[i], NULL, CONTINUE));
		verified_var_exist_in_env(cmd_args, env_list, i);
		i++;
	}
	return (0);
}

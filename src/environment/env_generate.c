/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_generate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 23:01:31 by lomorale          #+#    #+#             */
/*   Updated: 2025/04/21 22:59:04 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_var(t_list **env_list, char *var, int exported)
{
	t_list	*new_node;
	t_env	*new_var;

	new_var = (t_env *)malloc(sizeof(t_env));
	new_var->var = ft_strdup(var);
	if (!new_var->var)
		error_handle(ERR_UNKNOWN, "Minishell:",
			"exec_cmd.c:23\nft_strdup failed", KILL);
	new_var->exported = exported;
	new_node = ft_lstnew(new_var);
	if (!new_node)
		error_handle(ERR_UNKNOWN, "Minishell:",
			"exec_cmd.c:27\nft_lstnew failed", KILL);
	ft_lstadd_back(env_list, new_node);
}

char	**create_tmp_var(t_cmd *cmd)
{
	char	**tmp_vars;
	int		i;
	int		tab_size;

	i = 0;
	tab_size = count_table(cmd->cmd_args);
	tmp_vars = ft_calloc(sizeof(char *), tab_size + 1);
	while (i < tab_size)
	{
		tmp_vars[i] = ft_strdup(cmd->cmd_args[i]);
		i++;
	}
	tmp_vars[i] = 0;
	return (tmp_vars);
}

static void	check_for_update(t_list **tmp_head, t_env **tmp_var, char *var_name,
		char *value)
{
	while (*tmp_head)
	{
		if (!ft_strncmp_exact((*tmp_var)->var, var_name,
				var_len((*tmp_var)->var)))
		{
			update_var_value(tmp_var, value);
			return ;
		}
		else if (var_name[var_len(var_name) - 1] == '+')
		{
			if (!ft_strncmp_env_var(var_name, (*tmp_var)->var,
					var_len(var_name) - 1))
			{
				concat_var_value(tmp_var, value);
				return ;
			}
		}
		*tmp_head = (*tmp_head)->next;
		if (*tmp_head)
			(*tmp_var) = (t_env *)(*tmp_head)->content;
	}
}

char	**create_var(t_data *data, t_cmd *cmd)/*recheck this function*/
{
	t_list	*tmp_head;
	t_env	*tmp_var;
	char	*var_name;
	char	*value;
	int		i;

	if (cmd->type == TMP_VAR)
		return (create_tmp_var(cmd));
	i = 0;
	while (cmd->cmd_args[i])
	{
		var_name = ft_strndup(cmd->cmd_args[i], var_len(cmd->cmd_args[i]) + 1);
		value = ft_strdup(cmd->cmd_args[i] + (var_len(cmd->cmd_args[i]) + 1));
		tmp_head = data->env_list;
		tmp_var = (t_env *)(tmp_head)->content;
		check_for_update(&tmp_head, &tmp_var, var_name, value);
		if (!tmp_head)
			add_var(&data->env_list, cmd->cmd_args[i], 0);
		free(value);
		free(var_name);
		i++;
	}
	return (NULL);
}

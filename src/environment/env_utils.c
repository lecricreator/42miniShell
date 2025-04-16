/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 19:39:01 by odruke-s          #+#    #+#             */
/*   Updated: 2025/04/16 19:39:05 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*give_var_env_list(char *value, t_list *env_list)
{
	char	*tmp_content;
	int		size_value;

	size_value = (int)ft_strlen(value);
	while (env_list)
	{
		tmp_content = ((t_env *)(env_list)->content)->var;
		if (ft_strncmp_env_var(value, tmp_content, size_value) == 0)
			return (&tmp_content[size_value + 1]);
		env_list = env_list->next;
	}
	return (NULL);
}

void	write_env_list(char *value_modify, char *env_value, t_list **env_list)
{
	char	*tmp_content;
	t_list	*head_env;
	int		size_value;

	head_env = (*env_list);
	size_value = (int)ft_strlen(env_value);
	while ((*env_list))
	{
		tmp_content = (*env_list)->content;
		if (ft_strncmp_env_var(env_value, tmp_content, size_value) == 0)
			break ;
		(*env_list) = (*env_list)->next;
	}
	(*env_list)->content = ft_strjoin(env_value, value_modify);
	(*env_list) = head_env;
}

int	var_len(char *var)
{
	int	i;

	i = 0;
	while(var[i] && var[i] != '=')
		i++;
	return (i);
}

static void	add_var_value(t_env **var, char *new_value)
{
	char	*tmp;
	char	*var_name;

	tmp = (*var)->var;
	var_name = ft_strndup((*var)->var, var_len((*var)->var) + 1);
	(*var)->var = ft_strjoin(var_name, new_value);
	free(tmp);
	free(var_name);
	free(new_value);
}

static void	add_var(t_list **env_list, char *var)
{
	t_list	*new_node;
	t_env	*new_var;

	new_var = (t_env *)malloc(sizeof(t_env));
	new_var->var = ft_strdup(var);
	new_var->exported = 0;
	new_node = ft_lstnew(new_var);
	ft_lstadd_back(env_list, new_node);
}

char	*create_tmp_var(t_cmd *cmd)
{
	char	*tmp_var;

	tmp_var = ft_strdup(cmd->cmd_args[0]);
	return (tmp_var);
}

char	*create_var(t_data *data, t_cmd *cmd)
{
	t_list	*tmp_head;
	t_env	*tmp_var;
	char	*var_name;
	char	*value;

	if (cmd->type == TMP_VAR)
		return(create_tmp_var(cmd));
	var_name = ft_strndup(cmd->cmd_args[0], var_len(cmd->cmd_args[0]) + 1);
	value = ft_strdup(cmd->cmd_args[0] + (var_len(cmd->cmd_args[0]) + 1));
	tmp_head = data->env_list;
	tmp_var = (t_env *)(tmp_head)->content;
	while (tmp_head)
	{
		if (!ft_strncmp_exact(tmp_var->var, var_name, var_len(tmp_var->var)))
		{
			add_var_value(&tmp_var, value);
			free(var_name);
			return (NULL);
		}
		tmp_head = tmp_head->next;
		if (tmp_head)
			tmp_var = (t_env *)(tmp_head)->content;
	}
	add_var(&data->env_list, cmd->cmd_args[0]);
	free(value);
	free(var_name);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 19:39:01 by odruke-s          #+#    #+#             */
/*   Updated: 2025/04/19 15:46:30 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*give_var_env_list(char *var_name, t_list *env_list)
{
	char	*tmp_content;
	int		var_name_len;

	var_name_len = (int)ft_strlen(var_name);
	while (env_list)
	{
		tmp_content = ((t_env *)(env_list)->content)->var;
		if (ft_strncmp_env_var(var_name, tmp_content, var_name_len) == 0)
		{
			return (&tmp_content[var_name_len]);
		}
		env_list = env_list->next;
	}
	return (NULL);
}

void	write_env_list(char *value_modify, char *env_value, t_list **env_list)
{
	char	*tmp_content;
	t_list	*head_env;
	int		size_value;

	head_env = *env_list;
	size_value = (int)ft_strlen(env_value);
	while (*env_list)
	{
		tmp_content = ((t_env *)(*env_list)->content)->var;
		if (ft_strncmp_env_var(env_value, tmp_content, size_value) == 0)
		{
			break ;
		}
		*env_list = (*env_list)->next;
	}
	if (*env_list)
	{
		((t_env *)(*env_list)->content)->var = ft_strjoin(env_value, value_modify);
	}
	(*env_list) = head_env;
}

int	var_syntax(char *var)
{
	if (ft_isalpha(var[0]) || var[0] == '_')
		return (1);
	else
		return (0);
}

int	var_len(char *var)
{
	int	i;

	i = 0;
	while(var[i] && var[i] != '=')
		i++;
	return (i);
}

static void	update_var_value(t_env **var, char *new_value)
{
	char	*tmp;
	char	*var_name;

	tmp = NULL;
	var_name = NULL;
	tmp = (*var)->var;
	var_name = ft_strndup((*var)->var, var_len((*var)->var) + 1);
	(*var)->var = ft_strjoin(var_name, new_value);
	if (tmp)
		free(tmp);
	if (var_name)
		free(var_name);
}

static void	concat_var_value(t_env **var, char *new_value)
{
	char	*tmp;

	tmp = NULL;
		tmp = (*var)->var;
		(*var)->var = ft_strjoin((*var)->var, new_value);
	if (tmp)
		free(tmp);
}

void	add_var(t_list **env_list, char *var, int exported)
{
	t_list	*new_node;
	t_env	*new_var;

	new_var = (t_env *)malloc(sizeof(t_env));
	new_var->var = ft_strdup(var);
	new_var->exported = exported;
	new_node = ft_lstnew(new_var);
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
/*recheck this function*/
char	**create_var(t_data *data, t_cmd *cmd)
{
	t_list	*tmp_head;
	t_env	*tmp_var;
	char	*var_name;
	char	*value;
	int		i;

	if (cmd->type == TMP_VAR)
		return(create_tmp_var(cmd));
	i = 0;
	while (cmd->cmd_args[i])
	{
		var_name = ft_strndup(cmd->cmd_args[i], var_len(cmd->cmd_args[i]) + 1);
		value = ft_strdup(cmd->cmd_args[i] + (var_len(cmd->cmd_args[i]) + 1));
		tmp_head = data->env_list;
		tmp_var = (t_env *)(tmp_head)->content;
		while (tmp_head)
		{
			if (!ft_strncmp_exact(tmp_var->var, var_name, var_len(tmp_var->var)))
			{
				update_var_value(&tmp_var, value);
				break ;
			}
			else if (var_name[var_len(var_name) - 1] == '+')
			{
				if (!ft_strncmp_exact(tmp_var->var, var_name, var_len(tmp_var->var) - 1))
				{
					concat_var_value(&tmp_var, value);
					break ;
				}
			}
			tmp_head = tmp_head->next;
			if (tmp_head)
				tmp_var = (t_env *)(tmp_head)->content;
		}
		if (!tmp_head)
			add_var(&data->env_list, cmd->cmd_args[i], 0);
		free(value);
		free(var_name);
		i++;
	}
	return (NULL);
}

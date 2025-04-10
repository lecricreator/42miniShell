/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:34:03 by lomorale          #+#    #+#             */
/*   Updated: 2025/04/06 13:26:59 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_and_status(t_data *data)
{
	int	exit_code;
	int	child_exit;

	exit_code = 0;
	data->status = 0;
	while (data->n_fork--)
	{
		if (waitpid(data->pid, &data->status, 0) > 0)
		{
			if (WIFEXITED(data->status))
			{
				child_exit = WEXITSTATUS(data->status);
				if (child_exit != 0)
					exit_code = child_exit;
			}
			else if (WIFSIGNALED(data->status))
				exit_code = 127;
		}
	}
	return (exit_code);
}

void	print_token_list(t_list *token_list)
{
	t_token	*tmp_token;

	while (token_list)
	{
		tmp_token = (t_token *)token_list->content;
		printf("token = \"%s\"\ntype = %i\nindex = %i\n\n",
			tmp_token->str, tmp_token->type, tmp_token->index);
		token_list = token_list->next;
	}
}


static void	complete_path(char **path)
{
	int		i;
	char	*temp;

	i = 0;
	while (path[i])
	{
		temp = path[i];
		path[i] = ft_strjoin(temp, "/");
		free(temp);
		i++;
	}
}

char	**get_path(char **path, t_list *env)
{
	t_list	*tmp_head;

	tmp_head = env;
	while (tmp_head)
	{
		if (!ft_strncmp("PATH=", (char *)tmp_head->content, 5))
		{
			path = ft_split((char *)tmp_head->content + 5, ':');
			break ;
		}
		tmp_head = tmp_head->next;
	}
	if (!path)
		error_handle(NULL, "", "path not found", 1);
	complete_path(path);
	return (path);
}

int	is_builtin(t_type type)
{
	if (type <= 6)
		return (1);
	else
		return (0);
}

int	is_any_cmd(t_type type)
{
	if (is_builtin(type) || type == COMMAND)
		return (1);
	else
		return (0);
}

int	is_redir_op(t_type type)
{
	if (type >= 8 && type <= 10)
		return (1);
	else
		return (0);
}
char	*give_var_env_list(char *value, t_list *env_list)
{
	char	*tmp_content;
	int		size_value;

	size_value = (int)ft_strlen(value);
	while (env_list)
	{
		tmp_content = (env_list)->content;
		if (ft_strncmp(value, tmp_content, size_value) == 0)
			break ;
		env_list = env_list->next;
	}
	return (&tmp_content[size_value + 1]);
}

void	write_env_list(char *old_value, char *env_value, t_list **env_list)
{
	char	*tmp_content;
	t_list	*head_env;
	int		size_value;

	head_env = (*env_list);
	size_value = (int)ft_strlen(env_value);
	while ((*env_list))
	{
		tmp_content = (*env_list)->content;
		if (ft_strncmp(env_value, tmp_content, size_value) == 0)
			break ;
		(*env_list) = (*env_list)->next;
	}
	(*env_list)->content = ft_strjoin(env_value, old_value);
	(*env_list) = head_env;
}


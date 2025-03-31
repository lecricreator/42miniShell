/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:34:03 by lomorale          #+#    #+#             */
/*   Updated: 2025/03/27 11:46:04 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
int	wait_and_status(t_data *data)
{
	int	exit_code;
	int	child_exit;

	exit_code = 0;
	while (data->n_cmd--)
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
	free_data(data);
	return (exit_code);
}
*/
void	print_env(t_list *env_list)
{
	while (env_list)
	{
		printf("%s\n", (char *)env_list->content);
		env_list = env_list->next;
	}
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

void	get_env(t_list **env_list, char **env)
{
	char	*tmp_content;
	int		i;

	i = 0;
	tmp_content = NULL;
	while (env[i])
	{
		tmp_content = ft_strdup(env[i]);
		if (!tmp_content)
			return ;
		ft_lstadd_back(env_list, ft_lstnew(tmp_content));
		i++;
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
	t_list *tmp_head;

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
		error_handle(NULL , "", "path not found", 1);
	complete_path(path);
	return (path);
}

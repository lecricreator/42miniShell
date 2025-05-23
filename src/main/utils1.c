/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:34:03 by lomorale          #+#    #+#             */
/*   Updated: 2025/05/23 15:07:37 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (!ft_strncmp("PATH=", ((t_env *)(tmp_head)->content)->var, 5))
		{
			path = ft_split(((t_env *)(tmp_head)->content)->var + 5, ':');
			break ;
		}
		tmp_head = tmp_head->next;
	}
	if (path)
		complete_path(path);
	else
		return (NULL);
	return (path);
}

int	is_builtin(t_type type)
{
	if (type <= 6)
		return (1);
	else
		return (0);
}

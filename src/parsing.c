/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:26:38 by odruke-s          #+#    #+#             */
/*   Updated: 2025/03/27 12:00:56 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	parsing(t_data *data)
{
	lexing_tokens(data, data->input);
}

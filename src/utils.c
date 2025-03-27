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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_print_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 19:39:15 by odruke-s          #+#    #+#             */
/*   Updated: 2025/04/16 19:39:17 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_list *env_list)
{
	t_env	*tmp_var;

	tmp_var = (t_env *)env_list->content;
	while (env_list)
	{
		if (tmp_var->exported)
			printf("%s\n", tmp_var->var);
		env_list = env_list->next;
		if (env_list)
		tmp_var = (t_env *)env_list->content;
	}
}

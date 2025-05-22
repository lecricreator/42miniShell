/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in_pwd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:35:45 by lomorale          #+#    #+#             */
/*   Updated: 2025/04/21 22:29:49 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pwd(t_list *env)
{
	char	buffer[1024];
	char	*path;

	path = give_var_env_list("PWD", env);
	if (!path)
	{
		getcwd(buffer, sizeof(buffer));
		ft_printf_fd(1, "%s\n", buffer);
	}
	else
		ft_printf_fd(1, "%s\n", path);
	return (0);
}

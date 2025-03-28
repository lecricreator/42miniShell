/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:37:39 by lomorale          #+#    #+#             */
/*   Updated: 2025/03/28 19:56:26 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	exec_build_pwd()
{
	char	buffer[1024];

	if (getcwd(buffer, sizeof(buffer)) != NULL)
		return (0);
	else
		printf("%s\n", buffer);
	return (1);
}
int	exec_build_cd(char *str)
{
	(void)str;
}

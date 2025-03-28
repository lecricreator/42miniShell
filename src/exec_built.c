/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:37:39 by lomorale          #+#    #+#             */
/*   Updated: 2025/03/28 20:54:25 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	exec_pwd(void)
{
	char	buffer[1024];

	if (!getcwd(buffer, sizeof(buffer)))
		return (0);
	else
		printf("%s\n", buffer);
	return (1);
}
int	exec_cd(char *str)
{
	int	error_number;

	error_number = chdir(str);
	return (error_number);
}

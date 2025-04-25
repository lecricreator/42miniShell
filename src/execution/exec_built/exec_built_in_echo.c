/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in_echo.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:35:45 by lomorale          #+#    #+#             */
/*   Updated: 2025/04/25 11:55:08 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	exec_echo_write(char **cmd_args, int flags, int i)
// {
// 	int	n_appears;

// 	n_appears = 1000;
// 	if (flags != n_appears && i != 1)
// 		ft_printf_fd(1, " ");
// 	if (flags != -1 && cmd_args[i][0] == '-' && cmd_args[i][1] == 'n')
// 		flags = n_appears;
// 	else if (!cmd_args[i][0] == '\0')
// 	{
// 		ft_printf_fd(1, "%s", cmd_args[i]);
// 		flags--;
// 	}
// 	return (flags);
// }

// int	exec_echo(char **cmd_args)
// {
// 	int		i;
// 	int		flags;

// 	i = 0;
// 	flags = 0;
// 	while (cmd_args[++i])
// 	{
// 		flags = exec_echo_write(cmd_args, flags, i);
// 	}
// 	if (flags <= 0)
// 		ft_printf_fd(1, "\n");
// 	return (0);
// }


int	exec_echo(char **cmd_args)
{
	int		i;
	int		j;
	int		flags;
	int		return_line;
	int		first_write;

	i = 0;
	j = 0;
	flags = 1;
	return_line = 1;
	first_write = 1;
	while (cmd_args[++i])
	{
		if (flags && cmd_args[i][0] == '-')
		{
			while (cmd_args[i][++j] && flags == 1)
			{
				if (cmd_args[i][j] == 'n' || cmd_args[i][j] == '\0')
					flags = 1;
				else
				{
					ft_printf_fd(1, "%s", cmd_args[i]);
					flags = 0;
					return_line = 0;
					first_write = 0;
				}
			}
			if (i == 1 && flags)
				return_line = 0;
		}
		else
		{
			if (first_write)
			{
				ft_printf_fd(1, "%s", cmd_args[i]);
				first_write = 0;
			}
			else
				ft_printf_fd(1, " %s", cmd_args[i]);
		}
	}
	if (return_line == 1)
		ft_printf_fd(1, "\n");
	return (0);
}

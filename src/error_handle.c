/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:26:24 by odruke-s          #+#    #+#             */
/*   Updated: 2025/04/04 01:36:45 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_handle(t_data *data, char *cmd, char *msg, int terminate)
{
	int	exit_code;

	exit_code = 1;
	ft_printf_fd(2, "Minishell: %s: %s\n", cmd, msg);
	if (ft_strnstr(msg, "directory", ft_strlen(msg)) || ft_strnstr(msg,
			"permission", ft_strlen(msg)))
		exit_code = 126;
	else if (ft_strnstr(msg, "command", ft_strlen(msg)))
		exit_code = 127;
	if (terminate)
	{
		free_data(data);
		exit(exit_code);
	}
	else
		return (exit_code);
}

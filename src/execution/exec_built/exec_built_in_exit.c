/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in_exit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:41:24 by lomorale          #+#    #+#             */
/*   Updated: 2025/04/21 22:28:21 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_exit(void)
{
	t_data	*tmp_data;

	ft_printf_fd(2, "exit\n");
	tmp_data = recover_data_address(NULL);
	free_data(tmp_data);
	exit(EXIT_SUCCESS);
}

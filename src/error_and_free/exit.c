/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:25:08 by lomorale          #+#    #+#             */
/*   Updated: 2025/04/11 19:01:09 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit()
{
	t_data	*tmp_data;

	tmp_data = recover_data_address(NULL);
	free_data(tmp_data);
	exit(EXIT_SUCCESS);
}

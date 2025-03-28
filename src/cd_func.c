/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:31:50 by lomorale          #+#    #+#             */
/*   Updated: 2025/03/27 22:16:41 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void test_cd()
{
	char	s[100];

	printf("%s\n", getcwd(s, 100));
	if (chdir("src/") == -1)
		ft_printf_fd(2, "ERROR\n");
	else
		printf("%s\n", getcwd(s, 100));
}

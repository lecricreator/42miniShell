/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   lexing_miniutils.c                                  :+:    :+:           */
/*                                                      +:+                   */
/*   By: odruke-s <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/04/26 11:35:15 by odruke-s       #+#    #+#                */
/*   Updated: 2025/04/26 11:35:24 by odruke-s       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fordward_w_quote(char *input, int *i)
{
	(*i)++;
	while (input[*i] && input[*i] != 39)
		(*i)++;
}

void	init_mini_expand(t_mini_expan **ex)
{
	*ex = (t_mini_expan *)malloc(sizeof(t_mini_expan));
	(*ex)->i = 0;
	(*ex)->quotes = 0;
}

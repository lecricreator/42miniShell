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

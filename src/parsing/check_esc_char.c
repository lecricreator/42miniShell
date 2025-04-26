#include "minishell.h"

int is_in_quotes(int state, char c)
{
    if (c == 34)
    {
        if (state)
            return (0);
        else
            return (1);
    }
    else
        return (state);
}

static char	*esc_char(char *input, int *start)
{
    char    *str_front;
    char    *str_back;
    char    *new_input;
    int     i;

    i = *start + 1;
    str_front = NULL;
    str_back = NULL;
    new_input = NULL;
    str_front = ft_strndup(input, *start);
    str_back = ft_strdup(input + i);
    new_input = ft_strjoin(str_front, str_back);
    if (new_input[*start])
        *start += 1;
    free(str_front);
    free(str_back);
	return (new_input);
}

void	check_esc_char(char **input, int *i, int quotes)
{
	char	*tmp;
    char    *scp_on_quotes;

    scp_on_quotes = "\"\\$`";
	tmp = NULL;
    if (!quotes || (quotes && ft_strchr(scp_on_quotes, (*input)[*i + 1])))
    {
        tmp = *input;
        *input = esc_char(*input, i);
        free(tmp);
    }
}
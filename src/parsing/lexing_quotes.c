#include "minishell.h"

static char *handle_single_quote(char *input, int *i, int *closed)
{
    char    *res;
    int     b;

	(*closed) = 0;
	(*i)++;
    res = NULL;
    b = 0;
	while (input[*i] && !ft_isblank(input[*i]))
	{
		while (input[*i] != 39)
		{
			if (!*closed)
				(*closed) = 1;
			else
				(*closed) = 0;
			(*i)++;
        }
        if (!input[*i] && ft_isblank(input[*i]))
        {
            (*i)++;
            b++;
            break ;
        }
        res[b] = input[*i];
		(*i)++;
        b++;
	}
    res[b] = '\0';
	return (ft_strdup(res));
}

static char *handle_double_quote(char *input, int *i, int *closed)
{
    char    *res;
    int     b;

	(*closed) = 0;
	(*i)++;
    res = NULL;
    b = 0;
	while (input[*i] && !ft_isblank(input[*i]))
	{
		while (input[*i] != 34)
		{
			if (!*closed)
				(*closed) = 1;
			else
				(*closed) = 0;
			(*i)++;
        }
        if (!input[*i] && ft_isblank(input[*i]))
        {
            (*i)++;
            b++;
            break ;
        }
        res[b] = input[*i];
		(*i)++;
        b++;
	}
    res[b] = '\0';
	return (ft_strdup(res));
}

static char *handle_normal(char *input, int *i)
{
    char    *res;
    int     b;

    b = 0;
    res = NULL;
    while (input[*i] && input[*i] != 34 && input[*i] != 39)
    {
        res[b] = input[*i];
        (*i)++;
        b++;
    }
    res[b] = '\0';
    return (ft_strdup(res));
}

static char    *ft_next_chunk(char *input, int *i, int *closed)
{
    char    *res;

    if (input[*i] == 39)
        res = handle_single_quote(input, i, closed);
    else if (input[*i] == 34)
        res = handle_double_quote(input, i, closed);
    else
        res = handle_normal(input, i);
    return (res);
}

void	lexing_quotes(char **input)
{
	int	    closed;
    char    *tmp;
    char    *next_chunk;
    char    *res;
    int     i;

    i = 0;
    closed = 1;
    next_chunk = NULL;
    res = ft_strdup("");
    while ((*input)[i])
    {
        next_chunk = ft_next_chunk(*input, &i, &closed);  
        tmp = res;
        res = ft_strjoin(res, next_chunk);
        free(tmp);
        free(next_chunk);
    }
    tmp = *input;
    *input = res;
    free(tmp);
    if (!closed)
    {
        free(*input);
        *input = NULL;
        error_handle(ERR_UNKNOWN, "Unexpexted: ",
            "unclosed quotes not demanded by subject\n", CONTINUE); 
    }
}
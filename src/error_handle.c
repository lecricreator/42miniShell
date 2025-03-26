#include "minishell.h"
/*
static void	free_table(char **table)
{
	int	i;

	i = 0;
	while (table[i])
		free(table[i++]);
	free(table);
}
*/

static void	free_list(t_list **list)
{
	t_list *tmp;

	if (!list || !*list)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		free(*list);
		*list = tmp;
	}
	*list = NULL;
}

static void	free_data(t_data *data)
{
	if (data->input)
		free(data->input);
    if (data->env)
		free_list(&data->env);
	if (data)
		free(data);
}

int	error_handle(t_data *data, char *cmd, char *msg, int terminate)
{
	int	exit_code;

	exit_code = 1;
	ft_printf_fd(2, "bash: %s: %s\n", cmd, msg);
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
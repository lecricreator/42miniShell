/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:26:24 by odruke-s          #+#    #+#             */
/*   Updated: 2025/03/26 19:33:39 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
static void	free_token(void *token_void)
{
	t_token *token;

	token = (t_token *)token_void;
	if (token->str)
		free(token->str);
	free(token);
}

static void	free_list(t_list **list, void (*del)(void *))
{
	t_list *tmp;

	if (!list || !*list)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		if ((*list)->content && del)
			del((*list)->content);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
}

static void	free_data(t_data *data)
{
	if (data->input)
		free(data->input);
    if (data->env_list)
		free_list(&data->env_list, free);
	if (data->token_list)
		free_list(&data->token_list, free_token);
	if (data)
		free(data);
}
void	reset_input(t_data *data)
{
	if (data->input)
		free(data->input);
	if (data->token_list)
		free_list(&data->token_list, free_token);
}

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

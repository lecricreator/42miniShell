/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 02:08:38 by odruke-s          #+#    #+#             */
/*   Updated: 2025/04/04 02:09:26 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_table(char **table)
{
	int	i;

	i = 0;
	while (table[i])
		free(table[i++]);
	free(table);
}

void	free_token(void *token_void)
{
	t_token	*token;

	token = (t_token *)token_void;
	if (token->str)
		free(token->str);
	free(token);
}

static void	free_redir(void *redir_void)
{
	t_redir	*redir;

	redir = (t_redir *)redir_void;
	if (redir->filename)
		free(redir->filename);
}

void	free_cmd(void *cmd_void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)cmd_void;
	if (cmd->cmd_args)
		free_table(cmd->cmd_args);
	if (cmd->command_path)
		free(cmd->command_path);
	if (cmd->redir)
		free_list(&cmd->redir, free_redir);
	if (cmd)
		free(cmd);
}

void	reset_input(t_data *data)
{
	if (data->input)
	{
		free(data->input);
		data->input = NULL;
	}
	if (data->token_list)
		free_list(&data->token_list, free_token);
	if (data->cmd_list)
		free_list(&data->cmd_list, free_cmd);
	data->n_fork = 0;
	//if	(data->path)
	//	free_table(data->path);
}

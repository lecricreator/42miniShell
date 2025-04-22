/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 02:08:38 by odruke-s          #+#    #+#             */
/*   Updated: 2025/04/22 21:10:37 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_table(char **table)
{
	int	i;

	i = 0;
	if (!table)
		return ;
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

void	free_redir(void *redir_void)
{
	t_redir	*redir;

	redir = (t_redir *)redir_void;
	if (redir->filename)
		free(redir->filename);
	if (redir)
		free(redir);
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
	data->n_fork = 0;
	data->pid = 0;
	if (data->input)
	{
		free(data->input);
		data->input = NULL;
	}
	if (data->token_list)
		free_list(&data->token_list, free_token);
	if (data->cmd_list)
		free_list(&data->cmd_list, free_cmd);
}

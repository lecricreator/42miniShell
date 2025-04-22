/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_block_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 02:02:16 by odruke-s          #+#    #+#             */
/*   Updated: 2025/04/22 11:57:26 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_var_declaration(t_type type, int index)
{
	if ((type == ENV_VAR && !index) || (type == TMP_VAR && !index))
		return (1);
	else
		return (0);
}

int	var_tab_size(t_list *token_list)
{
	t_list	*tmp_head;
	t_token	*tmp_token;
	int		i;

	i = 0;
	tmp_head = token_list;
	tmp_token = (t_token *)tmp_head->content;
	while (tmp_head && (tmp_token->type == ENV_VAR
			|| tmp_token->type == TMP_VAR))
	{
		i++;
		tmp_head = tmp_head->next;
		if (tmp_head)
			tmp_token = (t_token *)tmp_head->content;
	}
	return (i);
}

void	init_redir(t_redir *redir)
{
	redir->filename = NULL;
	redir->type = NONE;
}

void	init_cmd(t_cmd *cmd)
{
	cmd->cmd_args = NULL;
	cmd->command_path = NULL;
	cmd->is_pipe = 0;
	cmd->redir = NULL;
	cmd->type = NONE;
}

void	fill_filename(t_list **token_list, t_token **tmp_token,
	t_redir	**redir_node)
{
	if (*token_list)
	{
		*tmp_token = (t_token *)(*token_list)->content;
		if ((*tmp_token)->type == FILENAME || (*tmp_token)->type == DELIMITER)
			(*redir_node)->filename = ft_strdup((*tmp_token)->str);
		else
		{
			free_redir(*redir_node);
			error_handle(ERR_UNKNOWN, (*tmp_token)->str,
				"command_block.c:45\nBad token type to redir", KILL);
		}
	}
	else
		error_handle(ERR_UNKNOWN, (*tmp_token)->str,
			"command_block.c:50\nNo file or delimiter to redir", KILL);
}

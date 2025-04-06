/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_block.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 02:02:16 by odruke-s          #+#    #+#             */
/*   Updated: 2025/04/04 02:02:18 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cmd_tab_len(t_list *token_list)
{
	t_list	*tmp_head;
	t_token	*tmp_token;
	int		i;

	i = 0;
	tmp_head = token_list;
	tmp_token = (t_token *)tmp_head->content;
	while (tmp_head && ((tmp_token->type == COMMAND && !i) || tmp_token->type == ARGUMENT))
	{
		i++;
		tmp_head = tmp_head->next;
		if (tmp_head)
		{
			tmp_token = (t_token *)tmp_head->content;
			if (tmp_token->type == OP_REDIR_OUT || tmp_token->type == OP_APPEND)
			{
				tmp_head = tmp_head->next;
				if (tmp_head)
					tmp_token = (t_token *)tmp_head->content;
				while (tmp_head && tmp_token->type == ARGUMENT)
				{
					i++;
					tmp_head = tmp_head->next;
					if (tmp_head)
						tmp_token = (t_token *)tmp_head->content;
				}
			}

		}
	}
	return (i);
}

/*extracts the currend command and his arguments into a 2D array, 
and sets the head of the token_list to the next operator, or the end of the command line*/
static char  **get_cmd_tab(t_data *data, t_list **token_list)
{
	t_token	*tmp_token;
	t_list	*save_position;
	char	**cmd_tab;
	int		i;

	i = 0;
	cmd_tab = ft_calloc(sizeof(char *), cmd_tab_len(*token_list) + 1);
	if (!cmd_tab)
		error_handle(data, "cmd_tab", "File: command_block || Function: get_cmd_tab || ft_calloc failed", 1);
	tmp_token = (t_token *)(*token_list)->content;
	while (*token_list && ((tmp_token->type == COMMAND && !i) || tmp_token->type == ARGUMENT))
	{
		cmd_tab[i++] = ft_strdup(tmp_token->str);
		save_position = (*token_list)->next;// check if this is correct assignation
		*token_list = (*token_list)->next;
		if (*token_list)
		{
			tmp_token = (t_token *)(*token_list)->content;
			if (tmp_token->type == OP_REDIR_OUT || tmp_token->type == OP_APPEND)
			{
				*token_list = (*token_list)->next;
				if (*token_list)
					tmp_token = (t_token *)(*token_list)->content;
				while (*token_list && tmp_token->type == ARGUMENT)
				{
					cmd_tab[i++] = ft_strdup(tmp_token->str);
					ft_lstdel_node(token_list, free_token);
					if (*token_list)
						tmp_token = (t_token *)(*token_list)->content;
				}
			}
		}
	}
	*token_list = save_position;//check if this is correct asignation
	return (cmd_tab);
}

void	init_redir(t_redir *redir)
{
	redir->filename = NULL;
	redir->type = NONE;
}

void	fill_redir(t_data *data, t_list **redir, t_list **token_list)//refactor this to set tokens after filename as arguments for the command and NOT fordward the token list
{
	t_token	*tmp_token;
	t_list	*new_node;
	t_redir	*redir_node;

	tmp_token = (t_token *)(*token_list)->content;
	redir_node = (t_redir *)malloc(sizeof(t_redir));
	if (!redir_node)
		error_handle(data, tmp_token->str, "command_block.c:106, malloc failed", 1);
	init_redir(redir_node);
	while (*token_list && (tmp_token->type >= 7 && tmp_token->type <= 11))
	{
		redir_node->type = tmp_token->type;
		*token_list = (*token_list)->next;
		if (*token_list)
		{
			tmp_token = (t_token *)(*token_list)->content;
			if (tmp_token->type == FILENAME)
			{
				redir_node->filename = ft_strdup(tmp_token->str);
				*token_list = (*token_list)->next;
			}
			else
				error_handle(data, "function: fill_redir", "no file to redir", 1);
		}
		new_node = ft_lstnew(redir_node);
		ft_lstadd_back(redir, new_node);
	}
}

static void	init_cmd(t_cmd *cmd)
{
	cmd->cmd_args = NULL;
	cmd->command_path = NULL;
	cmd->is_pipe = 0;
	cmd->redir = NULL;
	cmd->type = NONE;
}

t_cmd	*create_cmd(t_data *data, t_list **token_list)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		error_handle(data, "function create_cmd", "file: command_block malloc failed", 1);
	init_cmd(cmd);
	cmd->type = ((t_token *)(*token_list)->content)->type;
	cmd->cmd_args = get_cmd_tab(data, token_list);
	if (*token_list)
	{
		if (((t_token *)(*token_list)->content)->type == OP_PIPE)
		{
			cmd->redir = NULL;
			cmd->is_pipe = 1;
		}
		else
		{
			fill_redir(data, &cmd->redir, token_list);
			cmd->is_pipe = 0;
		}
	}
	else
	{
		cmd->is_pipe = 0;
		cmd->redir = NULL;
	}
	return (cmd);
}

void	fill_cmd_block(t_data *data, t_list **token_list, t_list **cmd_list)
{
	t_cmd	*cmd_node;
	t_list	*new_node;

	while (*token_list)
	{
		cmd_node = create_cmd(data, token_list);
		new_node = ft_lstnew(cmd_node);
		if(*token_list)
			*token_list = (*token_list)->next;
		ft_lstadd_back(cmd_list, new_node);
	}
}

void	create_cmd_block(t_data *data, t_list *token_list)
{
	t_token	*tmp_token;
	t_list	*tmp_head;

	tmp_head = token_list;
	while (tmp_head)
	{
		tmp_token = (t_token *)tmp_head->content;
		if ((tmp_token->type == COMMAND) || tmp_token->type <= 6)
			fill_cmd_block(data, &tmp_head, &data->cmd_list);
		if (tmp_token->type == OP_REDIR_OUT && tmp_token->index == 0) //starting with redir
			fill_cmd_block(data, &tmp_head, &data->cmd_list);// check this function to fill redir out without cmd when is the first token
	}
}

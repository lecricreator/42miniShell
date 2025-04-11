/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_block.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 02:02:16 by odruke-s          #+#    #+#             */
/*   Updated: 2025/04/06 11:25:33 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
static int	cmd_tab_len(t_list *token_list)// this function counts one more argument than it should, it could cause leaks
{
	t_list	*tmp_head;
	t_token	*tmp_token;
	int		i;

	i = 0;
	tmp_head = token_list;
	tmp_token = (t_token *)tmp_head->content;
	while (tmp_head && ((is_any_cmd(tmp_token->type) && !i) || tmp_token->type == ARGUMENT))
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
					tmp_head = tmp_head->next;
				if (tmp_head)
					tmp_token = (t_token *)(tmp_head)->content;
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
*/
/*
static int	cmd_tab_len_ri(t_list *token_list)
{
	t_list	*tmp_head;
	t_token	*tmp_token;
	int		i;

	i = 0;
	tmp_head = token_list->next;
	if (!tmp_head)
		return (i);
	tmp_head = tmp_head->next;
	if (!tmp_head)
		return (i);
	tmp_token = (t_token *)tmp_head->content;
	while (tmp_head && ((is_any_cmd(tmp_token->type) && !i) || tmp_token->type == ARGUMENT))
	{
			i++;
		tmp_head = tmp_head->next;
		if (tmp_head)
			tmp_token = (t_token *)tmp_head->content;
	}
	return (i);
}
*/
/*extracts the currend command and his arguments into a 2D array,
and sets the head of the token_list to the next operator, or the end of the command line*/
/*
static char  **get_cmd_tab(t_data *data, t_list **token_list)
{
	t_token	*tmp_token;
	t_list	*save_position;
	char	**cmd_tab;
	int		i;

	i = 0;
	cmd_tab = ft_calloc(sizeof(char *), cmd_tab_len(*token_list) + 1);
	if (!cmd_tab)
		error_handle(data, "cmd_tab", "command_block.c:88\nft_calloc failed", 1);
	tmp_token = (t_token *)(*token_list)->content;
	save_position = NULL;
	while (*token_list && ((is_any_cmd(tmp_token->type) && !i) || tmp_token->type == ARGUMENT))
	{
		cmd_tab[i++] = ft_strdup(tmp_token->str);
		save_position = (*token_list)->next;
		*token_list = (*token_list)->next;
		if (*token_list)
		{
			tmp_token = (t_token *)(*token_list)->content;
			if (tmp_token->type == OP_REDIR_OUT || tmp_token->type == OP_APPEND)
			{
				*token_list = (*token_list)->next;
				if (*token_list && (*token_list)->next)
				{
					tmp_token = ((t_token *)(*token_list)->next->content);
					while (*token_list && (*token_list)->next && tmp_token->type == ARGUMENT)
					{
						cmd_tab[i++] = ft_strdup(tmp_token->str);
						ft_lstdel_nxtnode(token_list, free_token);
						if (*token_list && (*token_list)->next)
							tmp_token = ((t_token *)(*token_list)->next->content);
					}
					tmp_token = ((t_token *)(*token_list)->content);
				}

			}
		}
	}
	if (save_position)
 		*token_list = save_position;
	return (cmd_tab);
}
*/
/*
static char  **get_heredoc(t_data *data, t_list **token_list)
{
	t_token	*tmp_token;
	char	**cmd_tab;
	int		i;

	i = 0;
	cmd_tab = ft_calloc(sizeof(char *), 3);
	if (!cmd_tab)
		error_handle(data, "cmd_tab", "command_block.c:132\nft_calloc failed", 1);

	tmp_token = (t_token *)(*token_list)->content;
	while (*token_list && ((tmp_token->type == OP_HEREDOC && !i ) || tmp_token->type == DELIMITER))
	{
		cmd_tab[i++] = ft_strdup(tmp_token->str);
		if (*token_list)
			tmp_token = (t_token *)(*token_list)->content;
	}
	return (cmd_tab);
}
*/
/*
static char  **get_cmd_tab_ri(t_data *data, t_list **token_list)
{
	t_token	*tmp_token;
	t_list	*save_position;
	char	**cmd_tab;
	int		i;

	i = 0;
	cmd_tab = ft_calloc(sizeof(char *), cmd_tab_len_ri(*token_list) + 1);
	if (!cmd_tab)
		error_handle(data, "cmd_tab", "command_block.c:154\nft_calloc failed", 1);

	save_position = *token_list;
	*token_list = (*token_list)->next;
	tmp_token = (t_token *)(*token_list)->next->content;
	while (*token_list && (*token_list)->next && ((is_any_cmd(tmp_token->type) && !i ) || tmp_token->type == ARGUMENT))
	{
		cmd_tab[i++] = ft_strdup(tmp_token->str);
		ft_lstdel_nxtnode(token_list, free_token);
		if (*token_list && (*token_list)->next)
			tmp_token = (t_token *)(*token_list)->next->content;
	}
	if (save_position)
 		*token_list = save_position;
	return (cmd_tab);
}
*/
void	init_redir(t_redir *redir)
{
	redir->filename = NULL;
	redir->type = NONE;
}

void	fill_redir(t_data *data, t_list **redir, t_list **token_list)
{
	t_token	*tmp_token;
	t_list	*new_node;
	t_redir	*redir_node;

	tmp_token = (t_token *)(*token_list)->content;
	while (*token_list && is_redir_op(tmp_token->type))// is this the correct range of type?
	{
		redir_node = (t_redir *)malloc(sizeof(t_redir));
		if (!redir_node)
			error_handle(data, tmp_token->str, "command_block.c:188\nMalloc failed", 1);
		init_redir(redir_node);
		redir_node->type = tmp_token->type;
		*token_list = (*token_list)->next;
		if (*token_list)
		{
			tmp_token = (t_token *)(*token_list)->content;
			if (tmp_token->type == FILENAME || tmp_token->type == DELIMITER)
				redir_node->filename = ft_strdup(tmp_token->str);
			else
			{
				free_redir(redir_node);
				error_handle(data, tmp_token->str, "command_block.c:200\nBad token type to redir", 1);//should this stop the program?
			}
		}
		else
			error_handle(data, tmp_token->str, "command_block.c:204\nNo file or delimiter to redir", 1);//should this stop the program?
		new_node = ft_lstnew(redir_node);
		ft_lstadd_back(redir, new_node);
		*token_list = (*token_list)->next;
		if (*token_list)
			tmp_token = (t_token *)(*token_list)->content;
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

/*
t_type	seek_type(t_list **token_list)
{
	t_list	*tmp_head;
	t_token	*tmp_token;

	tmp_head = *token_list;
	tmp_token = (t_token *)(tmp_head)->content;
	while (tmp_head && tmp_token->type)
	{
		if (tmp_token->type == COMMAND || is_any_cmd(tmp_token->type))
			return (tmp_token->type);
		tmp_head = tmp_head->next;
	}
	return (COMMAND);
}
*/
/*
t_cmd	*create_cmd(t_data *data, t_list **token_list)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		error_handle(data, "function create_cmd", "file: command_block malloc failed", 1);
	init_cmd(cmd);
	cmd->type = ((t_token *)(*token_list)->content)->type;
	if (cmd->type == OP_REDIR_IN)
	{
		cmd->type = seek_type(token_list);
		cmd->cmd_args = get_cmd_tab_ri(data, token_list);
	}
	else if (cmd->type == OP_HEREDOC)
		cmd->cmd_args = get_heredoc(data, token_list);
	else
		cmd->cmd_args = get_cmd_tab(data, token_list);
	if (*token_list)
	{
		fill_redir(data, &cmd->redir, token_list);
		if (*token_list && ((t_token *)(*token_list)->content)->type == OP_PIPE)
			cmd->is_pipe = 1;

	}
	return (cmd);
}
*/
static int	cmd_tab_len(t_list *token_list)
{
	t_list	*tmp_head;
	t_token	*tmp_token;
	int		i;

	i = 0;
	tmp_head = token_list;
	tmp_token = ((t_token *)(tmp_head)->content);
	while (tmp_head && tmp_token->type != OP_PIPE)
	{
		if ((is_any_cmd(tmp_token->type) && !i) || tmp_token->type == ARGUMENT)
			i++;
		if (is_any_cmd(tmp_token->type) && i > 1)
			break ;
		tmp_head = tmp_head->next;
		if (tmp_head)
			tmp_token = ((t_token *)(tmp_head)->content);
	}
	return (i);
}

static char  **get_cmd_tab(t_data *data, t_list **token_list)
{
	t_token	*tmp_token;
	char	**cmd_tab;
	int		i;

	i = 0;
	cmd_tab = ft_calloc(sizeof(char *), cmd_tab_len(*token_list) + 1);//implement alternative version for cmd_tab_len
	if (!cmd_tab)
		error_handle(data, "cmd_tab", "command_block.c:88\nft_calloc failed", 1);
	tmp_token = (t_token *)(*token_list)->content;
	while (*token_list && tmp_token->type != OP_PIPE)
	{
		if (is_any_cmd(tmp_token->type) || tmp_token->type == ARGUMENT)
			cmd_tab[i++] = ft_strdup(tmp_token->str);
		*token_list = (*token_list)->next;
		if (*token_list)
			tmp_token = ((t_token *)(*token_list)->content);
	}
	return (cmd_tab);
}

int	cmd_has_pipe(t_list *token_list)
{
	t_list	*tmp_head;
	t_token	*tmp_token;

	tmp_head = token_list;
	if (tmp_head)
		tmp_token = ((t_token *)(tmp_head)->content);
	while (tmp_head)
	{
		if (tmp_token->type == OP_PIPE)
			return (1);
		tmp_head = tmp_head->next;
		if (tmp_head)
			tmp_token = ((t_token *)(tmp_head)->content);
	}
	return (0);
}

t_cmd	*create_cmd(t_data *data, t_list **token_list)
{
	t_cmd	*cmd;
	t_list	*tmp_head;
	t_token	*tmp_token;

	tmp_head = *token_list;
	tmp_token = ((t_token *)(tmp_head)->content);
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		error_handle(data, "function create_cmd", "file: command_block malloc failed", 1);
	init_cmd(cmd);
	cmd->is_pipe = cmd_has_pipe(*token_list);
	while (tmp_head && tmp_token->type != OP_PIPE)
	{
		if (is_redir_op(tmp_token->type))
			fill_redir(data, &cmd->redir, &tmp_head);
		if (tmp_head)
			tmp_head = tmp_head->next;
		if (tmp_head)
			tmp_token = ((t_token *)(tmp_head)->content);
	}
	tmp_head = *token_list;
	tmp_token = ((t_token *)(tmp_head)->content);
	while (tmp_head && tmp_token->type != OP_PIPE)
	{
		if (is_any_cmd(tmp_token->type))
		{
			cmd->type = tmp_token->type;
			cmd->cmd_args = get_cmd_tab(data, token_list);
			break ;
		}
		tmp_head = tmp_head->next;
		if (tmp_head)
			tmp_token = ((t_token *)(tmp_head)->content);
	}
	return (cmd);
}

void	create_cmd_block(t_data *data, t_list *token_list, t_list **cmd_list)
{
	t_cmd	*cmd_node;
	t_list	*new_node;
	t_list	*tmp_head;

	tmp_head = token_list;
	while (tmp_head)
	{
		cmd_node = create_cmd(data, &tmp_head);
		new_node = ft_lstnew(cmd_node);
		ft_lstadd_back(cmd_list, new_node);
		if(tmp_head)
			tmp_head = tmp_head->next;
	}
}

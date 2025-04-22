/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_block.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 02:02:16 by odruke-s          #+#    #+#             */
/*   Updated: 2025/04/22 02:08:01 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_redir(t_redir *redir)
{
	redir->filename = NULL;
	redir->type = NONE;
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

static void	fill_redir(t_list **redir, t_list **token_list)
{
	t_token	*tmp_token;
	t_list	*new_node;
	t_redir	*redir_node;

	tmp_token = (t_token *)(*token_list)->content;
	while (*token_list && is_redir_op(tmp_token->type))// is this the correct range of type?
	{
		redir_node = (t_redir *)malloc(sizeof(t_redir));
		if (!redir_node)
			error_handle(ERR_UNKNOWN, tmp_token->str,
				"command_block.c:32\nMalloc failed", KILL);
		init_redir(redir_node);
		redir_node->type = tmp_token->type;
		*token_list = (*token_list)->next;
		fill_filename(token_list, &tmp_token, &redir_node);
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

static char  **get_cmd_tab(t_list **token_list)
{
	t_token	*tmp_token;
	char	**cmd_tab;
	int		i;

	i = 0;
	cmd_tab = ft_calloc(sizeof(char *), cmd_tab_len(*token_list) + 1);//implement alternative version for cmd_tab_len
	if (!cmd_tab)
		error_handle(ERR_UNKNOWN, "cmd_tab", "command_block.c:100\nft_calloc failed", KILL);
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
	while (tmp_head && (tmp_token->type == ENV_VAR || tmp_token->type == TMP_VAR))
	{
		i++;
		tmp_head = tmp_head->next;
		if (tmp_head)
			tmp_token = (t_token *)tmp_head->content;
	}
	return (i);
}


t_cmd	*cmd_if_var(t_cmd **cmd, t_list **token_list)
{
	int	i;
	int	tab_size;

	i = 0;
	tab_size = var_tab_size(*token_list);
	(*cmd)->cmd_args = ft_calloc(sizeof(char *), tab_size + 1);
	while (i < tab_size && *token_list)
	{
		(*cmd)->type = ((t_token *)(*token_list)->content)->type;
		(*cmd)->cmd_args[i++] = ft_strdup(((t_token *)(*token_list)->content)->str);
		if (i < tab_size)
			*token_list = (*token_list)->next;
	}
	(*cmd)->cmd_args[i] = NULL;
	return (*cmd);
}

void	fill_arg_and_redir(t_list **token_list, t_list **tmp_head, t_token **tmp_token,
		t_cmd **cmd)
{
	while (*tmp_head && (*tmp_token)->type != OP_PIPE)
	{
		if (is_redir_op((*tmp_token)->type))
			fill_redir(&(*cmd)->redir, tmp_head);
		if (*tmp_head)
			*tmp_head = (*tmp_head)->next;
		if (*tmp_head)
			(*tmp_token) = ((t_token *)(*tmp_head)->content);
	}
	(*tmp_token) = ((t_token *)(*token_list)->content);
	while (*token_list && (*tmp_token)->type != OP_PIPE)
	{
		if (is_any_cmd((*tmp_token)->type))
		{
			(*cmd)->type = (*tmp_token)->type;
			(*cmd)->cmd_args = get_cmd_tab(token_list);
			break ;
		}
		*token_list = (*token_list)->next;
		if (*token_list)
			(*tmp_token) = ((t_token *)(*token_list)->content);
	}
}

t_cmd	*create_cmd(t_list **token_list)
{
	t_cmd	*cmd;
	t_list	*tmp_head;
	t_token	*tmp_token;

	tmp_head = *token_list;
	tmp_token = ((t_token *)(tmp_head)->content);
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		error_handle(ERR_UNKNOWN, "Minishell:",
			"command_block.c:189\nmalloc failed", KILL);
	init_cmd(cmd);
	if (is_var_declaration(tmp_token->type, tmp_token->index))
		return (cmd_if_var(&cmd, token_list));
	cmd->is_pipe = cmd_has_pipe(*token_list);
	fill_arg_and_redir(token_list, &tmp_head, &tmp_token, &cmd);
	return (cmd);
}

void	create_cmd_block(t_list *token_list, t_list **cmd_list)
{
	t_cmd	*cmd_node;
	t_list	*new_node;
	t_list	*tmp_head;

	if (!token_list)
		return ;
	tmp_head = token_list;
	while (tmp_head)
	{
		cmd_node = create_cmd(&tmp_head);
		new_node = ft_lstnew(cmd_node);
		ft_lstadd_back(cmd_list, new_node);
		if(tmp_head)
			tmp_head = tmp_head->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_block.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 02:02:16 by odruke-s          #+#    #+#             */
/*   Updated: 2025/04/22 12:06:05 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_redir(t_list **redir, t_list **token_list)
{
	t_token	*tmp_token;
	t_list	*new_node;
	t_redir	*redir_node;

	tmp_token = (t_token *)(*token_list)->content;
	while (*token_list && is_redir_op(tmp_token->type))
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
		(*cmd)->cmd_args[i++]
			= ft_strdup(((t_token *)(*token_list)->content)->str);
		if (i < tab_size)
			*token_list = (*token_list)->next;
	}
	(*cmd)->cmd_args[i] = NULL;
	return (*cmd);
}

void	fill_arg_and_redir(t_list **token_list, t_list **tmp_head,
	t_token **tmp_token, t_cmd **cmd)
{
	while (*tmp_head && (*tmp_token)->type != OP_PIPE)
	{
		if (is_redir_op((*tmp_token)->type))
		{
			fill_redir(&(*cmd)->redir, tmp_head);
			break ;
		}
		// if (*tmp_head)
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

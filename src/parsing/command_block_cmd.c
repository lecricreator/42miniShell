/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_block_cmd.c                                 :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:49:16 by lomorale          #+#    #+#             */
/*   Updated: 2025/04/22 16:54:45 by odruke-s       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			"command_block_cmd.c:26\nmalloc failed", KILL);
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
		if (tmp_head)
			tmp_head = tmp_head->next;
	}
}

int	cmd_tab_len(t_list *token_list)
{
	t_list	*tmp_head;
	t_token	*tmp_token;
	int		i;

	i = 0;
	tmp_head = token_list;
	tmp_token = ((t_token *)(tmp_head)->content);
	while (tmp_head && tmp_token->type != OP_PIPE)
	{
		if (is_any_cmd(tmp_token->type) || tmp_token->type == ARGUMENT)
			i++;
		// if (is_any_cmd(tmp_token->type) && i > 1)
		// 	break ;
		tmp_head = tmp_head->next;
		if (tmp_head)
			tmp_token = ((t_token *)(tmp_head)->content);
	}
	return (i);
}

char	**get_cmd_tab(t_list **token_list)
{
	t_token	*tmp_token;
	char	**cmd_tab;
	int		i;

	i = 0;
	cmd_tab = ft_calloc(sizeof(char *), cmd_tab_len(*token_list) + 1);
	if (!cmd_tab)
		error_handle(ERR_UNKNOWN, "cmd_tab",
			"command_block.c:100\nft_calloc failed", KILL);
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

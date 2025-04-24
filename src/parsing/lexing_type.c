/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:04:24 by lomorale          #+#    #+#             */
/*   Updated: 2025/04/22 15:06:04 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	bad_type_next(char *token)
{
//	if (!ft_strncmp(token, "(", ft_strlen("(") + 1))
//		return (1);
//	if (!ft_strncmp(token, ")", ft_strlen(")") + 1))
//		return (1);
	if (!ft_strncmp(token, "\"", ft_strlen("\"") + 1))
		return (1);
	if (!ft_strncmp(token, "\'", ft_strlen("\'") + 1))
		return (1);
	if (!ft_strncmp(token, "!", ft_strlen("!") + 1))
		return (1);
	if (!ft_strncmp(token, ":", ft_strlen(":") + 1))
		return (1);
	return (0);
}

int	bad_type(char *token)
{
	if (!ft_strncmp(token, "||", ft_strlen("||") + 1))
		return (1);
	if (!ft_strncmp(token, "&&", ft_strlen("&&") + 1))
		return (1);
	if (!ft_strncmp(token, "&", ft_strlen("&") + 1))
		return (1);
	if (!ft_strncmp(token, ";;", ft_strlen(";;") + 1))
		return (1);
	if (!ft_strncmp(token, ";", ft_strlen(";") + 1))
		return (1);
//	if (!ft_strncmp(token, "{{", ft_strlen("{{") + 1))
//		return (1);
//	if (!ft_strncmp(token, "((", ft_strlen("((") + 1))
//		return (1);
//	if (!ft_strncmp(token, "}}", ft_strlen("}}") + 1))
//		return (1);
	return (bad_type_next(token));
}

static int	get_type_next(char *token)
{
	if (!ft_strncmp(token, "|", 2))
		return (OP_PIPE);
	if (!ft_strncmp(token, ">", 2))
		return (OP_REDIR_OUT);
	if (!ft_strncmp(token, "<", 2))
		return (OP_REDIR_IN);
	if (!ft_strncmp(token, ">>", 3))
		return (OP_APPEND);
	if (!ft_strncmp(token, "<<", 3))
		return (OP_HEREDOC);
	if (bad_type(token))
		return (BAD_TOKEN);
	if (ft_strchr(token, '='))
		if (var_syntax(token))
			return (ENV_VAR);
	return (UNKNOW);
}

int	get_type(char *token)
{
	if (!ft_strncmp(token, "echo", 5))
		return (BI_ECHO);
	if (!ft_strncmp(token, "cd", 3))
		return (BI_CD);
	if (!ft_strncmp(token, "pwd", 4))
		return (BI_PWD);
	if (!ft_strncmp(token, "export", 7))
		return (BI_EXPORT);
	if (!ft_strncmp(token, "unset", 6))
		return (BI_UNSET);
	if (!ft_strncmp(token, "env", 4))
		return (BI_ENV);
	if (!ft_strncmp(token, "exit", 5))
		return (BI_EXIT);
	return (get_type_next(token));
}

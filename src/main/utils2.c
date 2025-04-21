/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:34:03 by lomorale          #+#    #+#             */
/*   Updated: 2025/04/21 21:09:11 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief count the number of table.
 * @param table double table
 *
 * @return number of table
 */
int	count_table(char **table)
{
	int	i;

	i = 0;
	while (table[i])
	{
		i++;
	}
	return (i);
}

/**
 * @brief compare jusqu'au '='.
 * @param s1 string at compare with s2
 * @param s2 string at compare with s1
 * @param n number word at compare
 *
 * @return 0 true // supp false
 */
int	ft_strncmp_env_var(const char *var_name, const char *var_env, int var_name_len)
{
	int	i;
	int	var_env_len;

	i = 0;
	var_env_len = var_len((char *)var_env);
	if (var_env_len != var_name_len)
		return (1);
	while (i < var_env_len)
	{
		if (var_name[i] != var_env[i])
			return (((unsigned char *)var_name)[i] - ((unsigned char *)var_env)[i]);
		i++;
	}
	return (0);
}

char	*strdup_limiter(char *str, char stop)
{
	int		i;
	char	*tmp_var;

	i = -1;
	while (str[++i])
	{
		if (str[i] == stop)
			break ;
	}
	tmp_var = ft_calloc(sizeof(char), 1 + i);
	i = -1;
	while (str[++i])
	{
		if (str[i] == stop)
			break ;
		else
			tmp_var[i] = str[i];
	}
	return (tmp_var);
}

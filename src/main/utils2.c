/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:34:03 by lomorale          #+#    #+#             */
/*   Updated: 2025/04/17 12:21:38 by lomorale         ###   ########.fr       */
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
int	ft_strncmp_env_var(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	s2_len;

	i = 0;
	s2_len = (size_t)var_len((char *)s2);
	if (s2_len > n || n > s2_len)
	{
		if (n > s2_len)
			i = n;
		else
			i = s2_len;
		return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
	}
	while ((s1[i] || s2[i]) && i < n && s2[i] != '=')
	{
		if (s1[i] != s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
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

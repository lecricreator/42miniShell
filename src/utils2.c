/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:34:03 by lomorale          #+#    #+#             */
/*   Updated: 2025/04/10 20:23:30 by lomorale         ###   ########.fr       */
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

	i = 0;
	while ((s1[i] || s2[i]) && i < n && s2[i] != '=')
	{
		if (s1[i] != s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

char	*give_var_env_list(char *value, t_list *env_list)
{
	char	*tmp_content;
	int		size_value;

	size_value = (int)ft_strlen(value);
	while (env_list)
	{
		tmp_content = (env_list)->content;
		if (ft_strncmp_env_var(value, tmp_content, size_value) == 0)
			return (&tmp_content[size_value + 1]);
		env_list = env_list->next;
	}
	return (NULL);
}

void	write_env_list(char *value_modify, char *env_value, t_list **env_list)
{
	char	*tmp_content;
	t_list	*head_env;
	int		size_value;

	head_env = (*env_list);
	size_value = (int)ft_strlen(env_value);
	while ((*env_list))
	{
		tmp_content = (*env_list)->content;
		if (ft_strncmp_env_var(env_value, tmp_content, size_value) == 0)
			break ;
		(*env_list) = (*env_list)->next;
	}
	(*env_list)->content = ft_strjoin(env_value, value_modify);
	(*env_list) = head_env;
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

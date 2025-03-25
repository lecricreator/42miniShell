/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:27:47 by odruke-s          #+#    #+#             */
/*   Updated: 2024/10/02 18:00:58 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	int		ini;
	int		end;
	size_t	len;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	ini = 0;
	len = 0;
	while (s1[ini] && is_set(s1[ini], set))
		ini++;
	end = ft_strlen(s1) - 1;
	if (ini > end)
		return (ft_strdup(""));
	while (is_set(s1[end], set))
		end--;
	len = (end + 1) - ini;
	res = ft_calloc(sizeof(char), len + 1);
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1 + ini, len + 1);
	return (res);
}

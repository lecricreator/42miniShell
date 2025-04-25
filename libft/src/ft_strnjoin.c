/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomorale <lomorale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 01:25:45 by lomorale          #+#    #+#             */
/*   Updated: 2025/04/26 01:25:52 by lomorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*concatenate at most n characters of s2 in s1*/
char	*ft_strnjoin(char *s1, char const *s2, int n)
{
	char	*res;

	if (!s1)
		return (NULL);
	if (!s2)
		return (ft_strdup(s1));
	res = ft_calloc((ft_strlen(s1) + (n + 1)), sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1, ft_strlen(s1) + 1);
	ft_strlcpy(res + ft_strlen(s1), s2, n + 1);
	return (res);
}

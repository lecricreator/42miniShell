/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 17:00:14 by odruke-s          #+#    #+#             */
/*   Updated: 2024/10/01 17:30:34 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*cast_src;
	unsigned char	*cast_dst;
	size_t			i;

	i = 0;
	if (!dst && !src)
		return (NULL);
	cast_src = (unsigned char *)src;
	cast_dst = (unsigned char *)dst;
	if (dst > src)
		while (n-- > 0)
			cast_dst[n] = cast_src[n];
	else
	{
		while (i < n)
		{
			cast_dst[i] = cast_src[i];
			i++;
		}
	}
	return (dst);
}

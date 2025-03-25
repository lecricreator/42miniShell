/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:31:04 by odruke-s          #+#    #+#             */
/*   Updated: 2024/10/01 17:29:26 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*cast_dst;
	unsigned char	*cast_src;
	size_t			i;

	i = 0;
	if (!dst && !src)
		return (NULL);
	cast_dst = (unsigned char *)dst;
	cast_src = (unsigned char *)src;
	while (n > i)
	{
		cast_dst[i] = cast_src[i];
		i++;
	}
	return (dst);
}

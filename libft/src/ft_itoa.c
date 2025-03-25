/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:16:26 by odruke-s          #+#    #+#             */
/*   Updated: 2024/10/06 00:40:08 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nlen(int n)
{
	int	len;

	len = 1;
	if (n == -2147483648)
		n++;
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	while (n > 9)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*minint(char *res, int n, int len)
{
	res[0] = '-';
	res[1] = '2';
	n = 147483648;
	res[len] = '\0';
	while (n > 0)
	{
		len--;
		res[len] = 48 + (n % 10);
		n /= 10;
	}
	return (res);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		nlen;

	nlen = ft_nlen(n);
	res = (char *)malloc(sizeof(char) * (nlen + 1));
	if (!res)
		return (NULL);
	if (n == -2147483648)
		return (minint(res, n, nlen));
	if (n < 0)
	{
		n *= -1;
		res[0] = '-';
	}
	res[nlen--] = '\0';
	if (n == 0)
		res[0] = '0';
	while (n > 0)
	{
		res[nlen] = (n % 10) + 48;
		n /= 10;
		nlen--;
	}
	return (res);
}

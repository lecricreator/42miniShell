/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printunsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:54:40 by odruke-s          #+#    #+#             */
/*   Updated: 2024/10/24 12:52:01 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	num_len(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static char	*ft_uitoa(unsigned int n)
{
	char	*num;
	int		len;

	len = num_len(n);
	num = (char *)malloc(sizeof(char) * (len + 1));
	if (!num)
		return (0);
	num[len--] = '\0';
	if (n == 0)
		num[len] = (n % 10) + 48;
	while (n > 0)
	{
		num[len] = (n % 10) + 48;
		n /= 10;
		len--;
	}
	return (num);
}

int	ft_printunsigned(unsigned int n, t_flags flags)
{
	int		len;
	char	*num;

	len = num_len(n);
	num = ft_uitoa(n);
	if (flags.precision > 0)
	{
		flags.width = flags.precision;
		flags.zero_pad = 1;
	}
	if (flags.align)
	{
		ft_putstr(flags.fd, num);
		len += padding(&flags, num_len(n));
	}
	else
	{
		len += padding(&flags, num_len(n));
		ft_putstr(flags.fd, num);
	}
	free(num);
	return (len);
}

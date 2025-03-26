/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:06:13 by odruke-s          #+#    #+#             */
/*   Updated: 2025/03/04 11:15:16 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ptr_len(unsigned long long n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		len++;
		n /= 16;
	}
	return (len);
}

static void	ft_putptr(int fd, unsigned long long n)
{
	if (n == 0)
	{
		ft_printchar(fd, '0');
		return ;
	}
	if (n >= 16)
	{
		ft_putptr(fd, n / 16);
		ft_putptr(fd, n % 16);
	}
	else
	{
		if (n < 10)
			ft_printchar(fd, n + '0');
		else
			ft_printchar(fd, n - 10 + 'a');
	}
}

int	ft_printptr(unsigned long long ptr, t_flags flags)
{
	int	len;

	flags.zero_pad = 0;
	if (!ptr)
	{
		len = ft_putstr(flags.fd, "(nil)");
		return (len);
	}
	len = ptr_len(ptr);
	if (flags.align)
	{
		len += ft_putstr(flags.fd, "0x");
		ft_putptr(flags.fd, ptr);
		len += padding(&flags, ptr_len(ptr) + 2);
	}
	else
	{
		len += padding(&flags, ptr_len(ptr) + 2);
		len += ft_putstr(flags.fd, "0x");
		ft_putptr(flags.fd, ptr);
	}
	return (len);
}

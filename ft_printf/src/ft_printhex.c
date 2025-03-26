/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 20:17:47 by odruke-s          #+#    #+#             */
/*   Updated: 2024/10/24 12:45:57 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	hex_len(unsigned int n)
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

static int	hex_precision(t_flags *flags)
{
	int	len;

	len = 0;
	while (flags->precision > 0)
	{
		ft_printchar(flags->fd, '0');
		flags->precision--;
		len++;
	}
	return (len);
}

static void	ft_puthex(t_flags *flags, unsigned int n, const char format)
{
	if (n == 0)
	{
		ft_printchar(flags->fd, '0');
		return ;
	}
	if (n >= 16)
	{
		ft_puthex(flags, n / 16, format);
		ft_puthex(flags, n % 16, format);
	}
	else
	{
		if (n < 10)
			ft_printchar(flags->fd, n + '0');
		else
		{
			if (format == 'x')
				ft_printchar(flags->fd, n - 10 + 'a');
			if (format == 'X')
				ft_printchar(flags->fd, n - 10 + 'A');
		}
	}
}

static int	ft_prefix(int fd, unsigned int n, const char format)
{
	if (n > 0)
	{
		if (format == 'x')
			ft_putstr(fd, "0x");
		if (format == 'X')
			ft_putstr(fd, "0X");
		return (2);
	}
	else
		return (0);
}

int	ft_printhex(unsigned int n, const char format, t_flags flags)
{
	int	len;

	len = hex_len(n);
	if (flags.precision >= 0)
		flags.precision -= len;
	if (flags.align)
	{
		if (flags.hex_prefix)
			len += ft_prefix(flags.fd, n, format);
		len += hex_precision(&flags);
		ft_puthex(&flags, n, format);
		len += padding(&flags, len);
	}
	else
	{
		len += padding(&flags, len);
		if (flags.hex_prefix)
			len += ft_prefix(flags.fd, n, format);
		len += hex_precision(&flags);
		ft_puthex(&flags, n, format);
	}
	return (len);
}

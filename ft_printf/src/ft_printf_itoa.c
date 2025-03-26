/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_itoa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:16:26 by odruke-s          #+#    #+#             */
/*   Updated: 2024/10/24 12:44:57 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_process_precision(int len, t_flags *flags)
{
	if (flags->precision < 0)
	{
		flags->precision = 0;
		flags->width -= flags->precision;
	}
	flags->precision -= len;
	if (flags->precision < 0)
		flags->precision = 0;
}

static int	ft_nlen(int n, t_flags *flags)
{
	int	len;

	len = 1;
	if (n == -2147483648)
		n++;
	if (n < 0)
		n *= -1;
	while (n > 9)
	{
		n /= 10;
		len++;
	}
	ft_process_precision(len, flags);
	return (len);
}

static char	*minint(char *res, int len, t_flags *flags)
{
	int	n;

	n = 147483648;
	res[len--] = '\0';
	while (n > 0)
	{
		res[len--] = 48 + (n % 10);
		n /= 10;
	}
	res[len--] = '2';
	while (flags->precision)
	{
		res[len--] = '0';
		flags->precision--;
	}
	return (res);
}

static void	ft_process_res(char *res, int n, int len, t_flags *flags)
{
	if (n < 0)
		n *= -1;
	res[len--] = '\0';
	if (n == 0)
		res[0] = '0';
	while (n > 0)
	{
		res[len] = (n % 10) + 48;
		n /= 10;
		len--;
	}
	while (flags->precision)
	{
		res[len] = '0';
		flags->precision--;
		len--;
	}
}

char	*ft_printf_itoa(int n, t_flags *flags)
{
	char	*res;
	int		nlen;

	nlen = ft_nlen(n, flags) + flags->precision;
	res = (char *)malloc(sizeof(char) * (nlen + 1));
	if (!res)
		return (NULL);
	if (n == -2147483648)
		return (minint(res, nlen, flags));
	ft_process_res(res, n, nlen, flags);
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 12:21:40 by odruke-s          #+#    #+#             */
/*   Updated: 2025/03/05 15:35:58 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_convert(va_list args, const char format, t_flags flags)
{
	int	len;

	len = 0;
	if (format == 'c')
		len += ft_printchar_flag(va_arg(args, int), flags);
	else if (format == '%')
		len += ft_printchar_flag('%', flags);
	else if (format == 's')
		len += ft_printstr(va_arg(args, char *), flags);
	else if ((format == 'i') || (format == 'd'))
		len += ft_printnbr(va_arg(args, int), flags);
	else if (format == 'p')
		len += ft_printptr(va_arg(args, unsigned long long), flags);
	else if ((format == 'x') || (format == 'X'))
		len += ft_printhex(va_arg(args, unsigned int), format, flags);
	else if (format == 'u')
		len += ft_printunsigned(va_arg(args, unsigned int), flags);
	return (len);
}

static int	check_plh(const char *c)
{
	int		i;

	i = 1;
	if (*c == '%' && ft_strchr(PLH_LIST, c[i]))
		return (1);
	if (*c == '%' && (ft_strchr(FORMAT_LIST, c[i])))
	{
		while (*c == '%' && (ft_strchr(FORMAT_LIST, c[i])))
			i++;
		if (*c == '%' && c[i] && ft_strchr(PLH_LIST, c[i]))
			return (2);
	}
	return (0);
}

static int	ft_process(va_list args, const char *str, int *index, int fd)
{
	t_flags	flags;
	int		len;

	len = 0;
	flag_init(&flags, fd);
	(*index) += 1;
	ft_flags(&flags, str, index);
	len += ft_convert(args, str[(*index)], flags);
	return (len);
}

int	ft_printf_fd(int fd, const char *str, ...)
{
	va_list	args;
	t_flags	flags;
	int		len;
	int		index;

	index = -1;
	len = 0;
	va_start(args, str);
	flag_init(&flags, fd);
	if (!str)
		return (0);
	while (str[++index])
	{
		if (!check_plh(&str[index]))
			len += ft_printchar(flags.fd, str[index]);
		else if (check_plh(&str[index]) == 1)
			len += ft_convert(args, str[index++ + 1], flags);
		else if (check_plh(&str[index]) == 2)
			len += ft_process(args, str, &index, fd);
	}
	va_end(args);
	return (len);
}

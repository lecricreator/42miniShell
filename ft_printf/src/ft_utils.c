/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 21:04:01 by odruke-s          #+#    #+#             */
/*   Updated: 2024/10/24 12:47:22 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(int fd, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write (fd, &str[i], 1);
		i++;
	}
	return (i);
}

int	padding(t_flags *flags, int input_len)
{
	char	pad;
	int		len;

	len = 0;
	pad = ' ';
	if (flags->zero_pad)
		pad = '0';
	while (flags->width > input_len)
	{
		len += ft_printchar(flags->fd, pad);
		flags->width--;
	}
	return (len);
}

int	padding_nbr(t_flags *flags, int input_len)
{
	char		pad;
	size_t		len;

	len = 0;
	pad = ' ';
	if (flags->zero_pad && !flags->align && flags->precision < 0)
		pad = '0';
	if (flags->force_sign || flags->space_sign)
		flags->width -= 1;
	while (flags->width >= 0 && flags->width > (int)input_len)
	{
		len += ft_printchar(flags->fd, pad);
		flags->width--;
	}
	return (len);
}

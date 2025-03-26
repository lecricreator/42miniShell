/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:38:07 by odruke-s          #+#    #+#             */
/*   Updated: 2024/10/24 12:50:30 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_sign(int n, t_flags *flags)
{
	if (n >= 0 && (flags->force_sign || flags->space_sign))
	{
		if (flags->force_sign)
			ft_printchar(flags->fd, '+');
		else if (flags->space_sign)
			ft_printchar(flags->fd, ' ');
		return (1);
	}
	else if (n < 0)
	{
		ft_printchar(flags->fd, '-');
		return (1);
	}
	return (0);
}

static void	process_align(char *nbr, int n, int *len, t_flags *flags)
{
	if (n < 0)
		flags->width -= 1;
	if (!flags->align)
	{
		if (flags->zero_pad && flags->precision < 0)
			*len += ft_sign(n, flags);
		*len += padding_nbr(flags, ft_strlen(nbr));
		if (!flags->zero_pad || flags->precision >= 0)
			*len += ft_sign(n, flags);
		*len += ft_putstr(flags->fd, nbr);
	}
	else
	{
		*len += ft_sign(n, flags);
		*len += ft_putstr(flags->fd, nbr);
		*len += padding_nbr(flags, ft_strlen(nbr));
	}
}

int	ft_printnbr(int n, t_flags flags)
{
	int		len;
	int		temp;
	char	*nbr;

	len = 0;
	temp = flags.precision;
	if (!temp && !n)
		return (0);
	nbr = ft_printf_itoa(n, &flags);
	flags.precision = temp;
	process_align(nbr, n, &len, &flags);
	free(nbr);
	return (len);
}

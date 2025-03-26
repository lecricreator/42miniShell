/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 12:40:03 by odruke-s          #+#    #+#             */
/*   Updated: 2024/10/16 21:16:42 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printchar(int fd, const char c)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_printchar_flag(const char c, t_flags flags)
{
	int	len;

	len = 0;
	if (flags.width)
	{
		if (flags.align)
		{
			len += ft_printchar(flags.fd, c);
			while (0 < --flags.width)
				len += ft_printchar(flags.fd, ' ');
		}
		else
		{
			while (0 < --flags.width)
				len += ft_printchar(flags.fd, ' ');
			len += ft_printchar(flags.fd, c);
		}
	}
	else
		len += ft_printchar(flags.fd, c);
	return (len);
}

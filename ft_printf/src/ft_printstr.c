/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 21:30:31 by odruke-s          #+#    #+#             */
/*   Updated: 2024/10/25 21:45:28 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_process_align(char *str, int *len, t_flags *flags)
{
	int	i;
	int	wordlen;

	i = 0;
	if ((int)ft_strlen(str) > flags->precision)
		wordlen = ft_strlen(str) - (ft_strlen(str) - flags->precision);
	else
		wordlen = ft_strlen(str);
	if (flags->align)
	{
		while (flags->precision > i && str[i])
			*len += ft_printchar(flags->fd, str[i++]);
		*len += padding(flags, wordlen);
	}
	else
	{
		*len += wordlen;
		*len += padding(flags, wordlen);
		while (flags->precision > i && str[i])
			ft_printchar(flags->fd, str[i++]);
	}
}

int	ft_printstr(char *str, t_flags flags)
{
	int		len;
	char	*nu;

	len = 0;
	nu = "(null)";
	if (!str)
		str = nu;
	if (flags.precision < 0)
	{
		flags.precision = ft_strlen(str);
		ft_process_align(str, &len, &flags);
	}
	else
		ft_process_align(str, &len, &flags);
	return (len);
}

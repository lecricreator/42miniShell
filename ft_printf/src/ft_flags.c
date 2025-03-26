/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odruke-s <odruke-s@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 20:25:02 by odruke-s          #+#    #+#             */
/*   Updated: 2024/10/25 21:08:50 by odruke-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	flag_init(t_flags *flags, int fd)
{
	flags->align = 0;
	flags->zero_pad = 0;
	flags->force_sign = 0;
	flags->space_sign = 0;
	flags->hex_prefix = 0;
	flags->width = 0;
	flags->precision = -1;
	flags->fd = fd;
}

void	ft_precision_flags(t_flags *flags, const char *str, int *index)
{
	(*index) += 1;
	flags->precision = ft_atoi(&str[(*index)]);
	while (ft_isdigit(str[(*index)]))
		(*index)++;
}

void	ft_flags(t_flags *flags, const char *str, int *index)
{
	while (str[(*index)] != '.' && !ft_strchr(PLH_LIST, str[(*index)]))
	{
		if (str[(*index)] == '-')
			flags->align = 1;
		else if (str[(*index)] == '0')
			flags->zero_pad = 1;
		else if (str[(*index)] == '+')
			flags->force_sign = 1;
		else if (str[(*index)] == ' ')
			flags->space_sign = 1;
		else if (str[(*index)] == '#')
			flags->hex_prefix = 1;
		if (str[(*index)] != '0' && ft_isdigit(str[(*index)]))
		{
			flags->width = ft_atoi(&str[(*index)]);
			while (ft_isdigit(str[(*index)]))
				(*index)++;
		}
		else
			(*index)++;
	}
	if (str[*index] == '.')
		ft_precision_flags(flags, str, index);
}
